#pragma once
#include "../core/interfaces/Peripheral.hpp"
#include "../core/interfaces/EventEmitter.hpp"

class Actuator : public Peripheral, public EventEmitter<Actuator> {
public:

    enum class EventType { 
        CONNECTED, 
        CONNECTING 
    };
    
    Actuator(): Peripheral("rele_1") {
        emit(EventType::CONNECTED);
    }

    void loop() override {
        if (isActive()) {
            controlActuator();
        }
    }

    virtual void controlActuator() = 0;
};
