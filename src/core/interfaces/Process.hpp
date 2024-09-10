// src/core/interfaces/Process.hpp

#pragma once
#include "Component.hpp"
#include "../Core.hpp"


class Process : public Component {
protected:
    int priority;

public:
    Process(const std::string& name, int priority) : Component(name), priority(priority) {
        Core::getInstance().registerProcess(this);
    }

    virtual void setup() = 0;
    virtual void loop() = 0;

    int getPriority() const {
        return priority;
    }
};