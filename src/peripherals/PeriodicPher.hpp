#pragma once
#include <Arduino.h>
#include "../core/interfaces/Peripheral.hpp"
#include "../core/interfaces/EventEmitter.hpp"

class PeriodicPher : public Peripheral, public EventEmitter<PeriodicPher> {
protected:
    unsigned long interval;
    unsigned long lastRun;

public:
    PeriodicPher(const std::string& name, unsigned long interval) 
    : Peripheral(name), interval(interval), lastRun(0) {};

    enum class EventType { CONNECTED, CONNECTING };

    void loop() override {
        unsigned long currentMillis = millis();
        if (currentMillis - lastRun >= interval && isActive()) {
            readSensor();
            lastRun = currentMillis;
        }
    }

    virtual void readSensor() = 0;
};
