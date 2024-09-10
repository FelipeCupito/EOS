// src/core/interfaces/Component.hpp

#pragma once
#include <string>

class Component {
protected:
    std::string name;

public:
    Component(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }

    virtual void setup() = 0;
    virtual void loop() = 0;
};

