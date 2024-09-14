#ifndef CORE_CONFIG_HPP
#define CORE_CONFIG_HPP

#include "Core.hpp"
#include "WiFiManager.hpp"
#include "Logger.hpp"
#include "EventManager.hpp"

enum class ModuleID {
    WiFi,
    Logger,
    EventManager,
    COUNT
};

class CoreConfig {
public:

    CoreConfig& enableModule(ModuleID id, bool enabled) {
        enabledModules_[static_cast<std::size_t>(id)] = enabled;
        return *this;
    }

    void apply() const {
        auto& coreInstance = Core::getInstance();

        // Inicializar módulos según configuración
        if (enabledModules_[static_cast<std::size_t>(ModuleID::WiFi)]) {
            coreInstance.registerModule(std::make_unique<WiFiManager>());
        }

        if (enabledModules_[static_cast<std::size_t>(ModuleID::Logger)]) {
            coreInstance.registerModule(std::make_unique<Logger>());
        }

        if (enabledModules_[static_cast<std::size_t>(ModuleID::EventManager)]) {
            coreInstance.registerModule(std::make_unique<EventManager>());
        }

        // Ejecutar el setup de Core
        coreInstance.setup();
    }

    // Deshabilitar los módulos en tiempo de ejecución
    void disableModule(ModuleID id) {
        auto& coreInstance = Core::getInstance();
        coreInstance.disableModule(id);
    }

private:
    std::array<bool, static_cast<std::size_t>(ModuleID::COUNT)> enabledModules_ = {};  // Inicializado a `false`
};

#endif // CORE_CONFIG_HPP
