#include "Core.hpp"
#include "SystemManager.hpp"
#include "EventBus.hpp"
#include "./interfaces/Peripheral.hpp"
#include "./interfaces/Process.hpp"
#include "./interfaces/ServiceProvider.hpp"

void Core::setup() {
    SystemManager::getInstance().setup();
}

void Core::loop() {
    SystemManager::getInstance().loop();
}

void Core::registerPeripheral(Peripheral* peripheral) {
    SystemManager::getInstance().addPeripheral(peripheral);
}

void Core::registerProcess(Process* process) {
    SystemManager::getInstance().addProcess(process);
}

template <typename Derived, std::size_t SIZE>
typename Derived::ServiceAccessor* Core::getServiceProxy(const std::string& peripheralName) {
    
    auto* peripheral = SystemManager::getInstance().getPeripheral(peripheralName);
    
    // Asegúrate de hacer el cast con ambos parámetros de plantilla: Derived y SIZE
    auto* serviceCapable = dynamic_cast<ServiceProvider<Derived, SIZE>*>(peripheral);

    if (!serviceCapable) {
        // Manejo de error
        return nullptr;
    }

    return serviceCapable->getServiceProxy();
}

// template <typename Derived>
// typename Derived::ServiceAccessor* Core::getServiceProxy(const std::string& peripheralName) {
//     auto* peripheral = SystemManager::getInstance().getPeripheral(peripheralName);
    
//     auto* serviceCapable = dynamic_cast<ServiceProvider<Derived>*>(peripheral);

//     if (!serviceCapable) {
//         // Manejo de error
//         return nullptr;
//     }

//     return dynamic_cast<typename Derived::ServiceAccessor*>(serviceCapable->getServiceProxy());
// }

template<typename Derived>
void Core::publishEvent(EventEmitter<Derived>* emitter, typename Derived::EventType event) {
    EventBus::getInstance().publishEvent(emitter, event);
}

template<typename Derived>
void Core::subscribeToEvent(EventEmitter<Derived>* emitter, typename Derived::EventType event, std::function<void()> callback) {
    EventBus::getInstance().subscribeToEvent(emitter, event, callback);
}

