#include "../core/Core.hpp"
#include "../core/interfaces/Process.hpp"
#include "../peripherals/sensorWithService.hpp"


class CoolingSystemProcess : public Process {
public:
    CoolingSystemProcess() : Process("cooling_system", 1) {}

    void setup() override {
        // Obtener el proxy del servicio de temperatura registrado sin especificar el número de servicios
        auto proxy = Core::getInstance().getServiceApi<TemperatureSensorService>("temp_sensor_1");

        if (proxy) {
            // Verificar si el servicio de temperatura está registrado antes de invocarlo
            if (proxy->hasService(static_cast<std::size_t>(TemperatureSensorService::ServiceName::readTemperature))) {
                // Llamar al servicio de temperatura
                int currentTemp = proxy->invokeService(static_cast<std::size_t>(TemperatureSensorService::ServiceName::readTemperature));
                if (currentTemp > 30) {
                    handleOverheat();
                }
            } else {
                // Manejo de error si el servicio no está disponible
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
