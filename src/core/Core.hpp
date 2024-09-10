// // src/core/Core.hpp
#pragma once
#include <string>
#include <functional>

// Forward declarations
class Peripheral;
class Process;
class EventBus;
class SystemManager;
template<typename Derived>
class EventEmitter;

class Core {
private:
    // Constructor privado para Singleton
    Core() = default;

public:
    // Singleton
    static Core& getInstance() {
        static Core instance;
        return instance;
    }

    // Prohibido el uso de copia o asignación
    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;

    void setup();
    void loop();

    // Registra un periférico en el sistema
    void registerPeripheral(Peripheral* peripheral);
    void registerProcess(Process* process);

    // Service proxy
    template <typename Derived, std::size_t SIZE>
    typename Derived::ServiceAccessor* getServiceProxy(const std::string& peripheralName);

    // Event bus
    template<typename Derived>
    void publishEvent(EventEmitter<Derived>* emitter, typename Derived::EventType event);

    template<typename Derived>
    void subscribeToEvent(EventEmitter<Derived>* emitter, typename Derived::EventType event, std::function<void()> callback);
};

// class Core {
// private:
//     SystemManager& systemManager = SystemManager::getInstance();
//     EventBus eventBus = EventBus::getInstance();

// public:
//     static Core& getInstance() {
//         static Core instance;
//         return instance;
//     }

//     void setup() {
//         systemManager.setup();
//     }

//     void loop() {
//         systemManager.loop();
//     }

//     /** SysteManager **/
//     void registerPeripheral(Peripheral* peripheral) {
//         systemManager.addPeripheral(peripheral);
//     }

//     void registerProcess(Process* process) {
//         systemManager.addProcess(process);
//     }


//     /** Service proxy. **/
//     // Obtener un proxy de servicio con manejo de errores
//     template <typename Derived>
//     typename Derived::ServiceAccessor* getServiceProxy(const std::string& peripheralName) {
//         auto* peripheral = getPeripheral(peripheralName);
//         auto* serviceCapable = dynamic_cast<ServiceProvider<Derived>*>(peripheral);
        
//         if (!serviceCapable) {
//             //TODO, manejo de error, deberia ser un erro de compilacion pero no se puede hacer con dynamic_cast
//         }

//         return dynamic_cast<typename Derived::ServiceAccessor*>(serviceCapable->getServiceProxy());
//     }

//     /** event bus **/
//     template<typename Derived>
//     void publishEvent(EventEmitter<Derived>* emitter, typename Derived::EventType event) {
//         eventBus.publishEvent(emitter, event);
//     }

//     template<typename Derived>
//     void subscribeToEvent(EventEmitter<Derived>* emitter, typename Derived::EventType event, std::function<void()> callback) {
//         eventBus.subscribeToEvent(emitter, event, callback);
//     }
// };
