#ifndef WIFI_MANAGER_HPP
#define WIFI_MANAGER_HPP

#include <iostream>
#include <memory> // Para usar unique_ptr
#include "Module.hpp"

class WiFiManager : public Module {
public:
    // Uso de unique_ptr para asegurar que el objeto se gestiona correctamente
    static std::unique_ptr<WiFiManager>& getInstance() {
        if (!instance_) {
            instance_ = std::make_unique<WiFiManager>();  // Crear instancia si no existe
        }
        return instance_;
    }

    void connect() {
        std::cout << "Connecting to Wi-Fi..." << std::endl;
        // Lógica de conexión Wi-Fi
    }

    void disconnect() {
        std::cout << "Disconnecting from Wi-Fi..." << std::endl;
        // Lógica de desconexión Wi-Fi
    }

private:
    WiFiManager() = default;
    static std::unique_ptr<WiFiManager> instance_;  // Puntero único a la instancia
};

// Definición del puntero estático
std::unique_ptr<WiFiManager> WiFiManager::instance_ = nullptr;

#endif // WIFI_MANAGER_HPP

#ifndef WIFI_MANAGER_HPP
#define WIFI_MANAGER_HPP


#include <iostream>

class WiFiManager : public Module {
public:
    WiFiManager() = default;

    void initialize() override {
        std::cout << "Initializing Wi-Fi..." << std::endl;
        // Lógica de inicialización del Wi-Fi
    }

    ModuleID getID() const override {
        return ModuleID::WiFi;
    }

    ~WiFiManager() {
        std::cout << "Wi-Fi Manager destroyed." << std::endl;
    }
};

#endif // WIFI_MANAGER_HPP