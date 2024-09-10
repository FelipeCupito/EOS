#include <Arduino.h>
#include "../core/interfaces/Peripheral.hpp"

class Led : public Peripheral {
public:

    const int pin;



    Led(const char* name, const int pin) : Peripheral(name), pin(pin) {
       
    }

    void setup() {
        pinMode(pin, OUTPUT);
    }

    void loop() {

        blink();
    }

    void blink() {
        digitalWrite(pin, HIGH);
        delay(500);
        digitalWrite(pin, LOW);
        delay(500);

    }
};
