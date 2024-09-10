#include "../core/Core.hpp"
#include "../core/interfaces/Process.hpp"
#include "../peripherals/sensorWithService.hpp"


class CoolingSystemProcess : public Process {
public:
    CoolingSystemProcess() : Process("cooling_system", 1) {}

    void setup() override {
        // Obtener el proxy del servicio de temperatura registrado de forma simple y segura
        //auto proxy = Core::getInstance().getServiceProxy<TemperatureSensorService>("temp_sensor_1");
        auto proxy = Core::getInstance().getServiceProxy<TemperatureSensorService, 2>("temp_sensor_1");

        if (proxy) {
            // Llamar al servicio de temperatura
            int currentTemp = proxy->invokeService(TemperatureSensorService::ServiceName::readTemperature);
            if (currentTemp > 30) {
                handleOverheat();
            }
        }
    }

    void loop() override {
        // Lógica continua
    }

    void handleOverheat() {
        //Serial.println("Overheat detected! Activating cooling system.");
    }
};
