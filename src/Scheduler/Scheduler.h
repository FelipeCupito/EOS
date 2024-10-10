#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <Arduino.h>

// Definir constante para ESP8266
#define DEFAULT_STACK_SIZE 512
#define STACK_MAX (0x2000 + 0x4000) // ESP8266 reserva 4096 bytes para el stack

/**
 * Syntactic sugar for scheduler based busy-wait for condition;
 * yield until condition is valid. May require volatile condition
 * variable(s).
 */
#define await(cond) while (!(cond)) yield()


class SchedulerClass {
public:
    using func_t = void (*)();

    /**
     * @brief Inicia el scheduler con el tamaño de pila especificado.
     * @param stackSize Tamaño de la pila en bytes.
     * @return true si se inició correctamente, false en caso contrario.
     */
    static bool begin(size_t stackSize);

    /**
     * @brief Inicia una tarea con las funciones y tamaño de pila especificados.
     * @param taskSetup Función de configuración de la tarea (puede ser NULL).
     * @param taskLoop Función principal de la tarea (no puede ser NULL).
     * @param stackSize Tamaño de la pila en bytes.
     * @return true si se inició correctamente, false en caso contrario.
     */
    static bool start(func_t taskSetup, func_t taskLoop, size_t stackSize = DEFAULT_STACK_SIZE);

    /**
     * @brief Realiza un cambio de contexto a la siguiente tarea en la cola.
     */
    static void yield();

    /**
     * @brief Obtiene el tamaño de la pila de la tarea actual.
     * @return Tamaño de la pila en bytes.
     */
    static size_t stack();

protected:
    // Estructura para representar una tarea
    struct task_t {
        task_t* next;        // Puntero a la siguiente tarea
        task_t* prev;        // Puntero a la tarea anterior
        jmp_buf context;     // Contexto de la tarea para setjmp/longjmp
        const uint8_t* stack; // Puntero al inicio de la pila de la tarea
    };

    // Métodos protegidos
    static void init(func_t setup, func_t loop, const uint8_t* stack);

    // Miembros estáticos
    static task_t s_main;       // Tarea principal
    static task_t* s_running;   // Tarea en ejecución
    static size_t s_top;        // Tope de la pila para asignación de tareas

private:
    // Constructor privado para el singleton
    SchedulerClass() {}
};

// Declaración del singleton
extern SchedulerClass Scheduler;

#endif // SCHEDULER_H
