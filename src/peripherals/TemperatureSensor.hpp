#include "../core/interfaces/Peripheral.hpp"
#include "../core/interfaces/SharedStorage.hpp"

class TemperatureSensor : public SharedStorage<TemperatureSensor, 2>, public Peripheral {
public:
    //Enum que define las variables
    enum class VariableName {
        temperature = 0,
        humidity
    };

    int temperature;
    int humidity;

    TemperatureSensor(const char* name) : Peripheral(name) {
        // Usamos el macro para registrar las variables
        REGISTER_SHARED_VAR(temperature, SharedStorage::ACCESSTYPE::READWRITE);
        REGISTER_SHARED_VAR_READ(humidity);
    }


    void setup() override {
        // Inicialización
    }

    void loop() override {
        // Simulación de lecturas
        temperature = random();
        humidity = random();
    }
};
