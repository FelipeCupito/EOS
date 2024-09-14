#ifndef MODULE_HPP
#define MODULE_HPP

#include "CoreConfig.hpp"

class Module {
public:
    virtual void initialize() = 0;  // Método para inicializar el módulo
    virtual ModuleID getID() const = 0;  // Cada módulo tendrá un ID único
    virtual ~Module() = default;
};

#endif // MODULE_HPP
