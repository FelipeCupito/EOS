#include <Arduino.h>

#include "./peripherals/Led.hpp"
#include "./peripherals/TemperatureSensor.hpp"
#include "./peripherals/sensorWithService.hpp"
#include "./processes/CoolingSystemProcess.hpp"

void setup() {

  TemperatureSensor tp = TemperatureSensor("temp_sensor_1");

  TemperatureSensorService tpService = TemperatureSensorService("temp_sensor_1");

  CoolingSystemProcess coolingSystem = CoolingSystemProcess();

  
  Led led = Led("led", 13);
}

void loop() {
}
