// src/core/SystemManager.hpp

#pragma once
#include <vector>
#include <string>

// Forward declarations
class Peripheral;
class Process;

class SystemManager {
    //TODO: implemenatr scheduler con prioridad para procesos
    //TODO: implementar que los preocesos y los perifericos sea no bloqueantes
private:
    // Usamos vectores en lugar de mapas para eficiencia en pequeñas colecciones
    std::vector<Peripheral*> peripherals;
    std::vector<Process*> processes;

    // Constructor privado para Singleton
    SystemManager() = default;

public:
    // Patrón Singleton
    static SystemManager& getInstance() {
        static SystemManager instance;
        return instance;
    }

    // Prohibir copia y asignación
    SystemManager(const SystemManager&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;

    void setup();
    void loop();

    // Métodos para añadir y gestionar periféricos y procesos
    void addPeripheral(Peripheral* peripheral);
    void addProcess(Process* process);

    Peripheral* getPeripheral(const std::string& name);
    Process* getProcess(const std::string& name);
    

};


// #pragma once
// #include <vector>
// #include "./interfaces/Peripheral.hpp"
// #include "./interfaces/Process.hpp"

// class SystemManager {
// private:
//     // Usamos vectores en lugar de mapas para eficiencia en pequeñas colecciones
//     std::vector<Peripheral*> peripherals;
//     std::vector<Process*> processes;

// public:

//     void addPeripheral(Peripheral* peripheral) {
//         peripherals.push_back(peripheral);
//     }

//     void addProcess(Process* process) {
//         processes.push_back(process);
//     }

//     // Obtener un periférico por nombre
//     Peripheral* getPeripheral(const std::string& name) {
//         for (auto* peripheral : peripherals) {
//             if (peripheral->getName() == name) {
//                 return peripheral;
//             }
//         }
//         return nullptr;  // Si no se encuentra
//     }

//     // Obtener un proceso por nombre
//     Process* getProcess(const std::string& name) {
//         for (auto* process : processes) {
//             if (process->getName() == name) {
//                 return process;
//             }
//         }
//         return nullptr;  // Si no se encuentra
//     }

//     // Ejecutar setup y loop para todos los periféricos y procesos
//     void setup() {
//         for (Peripheral* peripheral : peripherals) {
//             peripheral->setup();
//         }
//         for (Process* process : processes) {
//             process->setup();
//         }
//     }

//     void loop() {
//         for (Peripheral* peripheral : peripherals) {
//             peripheral->loop();
//         }
//         for (Process* process : processes) {
//             process->loop();
//         }
//     }
// };
