#pragma once
#include "../core/interfaces/Peripheral.hpp"
#include "../core/interfaces/EventEmitter.hpp"
#include "../core/interfaces/ServiceProvider.hpp"

class TemperatureSensorService : public Peripheral, public ServiceProvider<TemperatureSensorService, 1> {
public:

    enum class ServiceName {
        readTemperature,
        COUNT
    };

    TemperatureSensorService(const std::string& name): Peripheral(name) {

        REGISTER_SERVICE(ServiceName::readTemperature, &TemperatureSensorService::readTemperature);
    }


    void setup() override {
        // Configuración inicial del sensor
    }

    void loop() override {
        // Simulación de lectura de temperatura
        readTemperature();
    }

    
    int readTemperature() {
        // Lectura simulada
        return random();
    }
};
