// src/core/interfaces/ServiceProvider.hpp

#pragma once
#include <array>
#include <functional>
#include <type_traits>
#include <cstddef>

#define REGISTER_SERVICE(serviceName, method) registerService(static_cast<std::size_t>(serviceName), method)
// #define REGISTER_SERVICE_ey(serviceName) registerService(static_cast<std::size_t>(ServiceName::serviceName), &Derived::serviceName)


template<typename Derived, std::size_t SIZE>
class ServiceProvider {
public:
    // Array de funciones para almacenar los servicios
    std::array<std::function<int(Derived*)>, SIZE> serviceArray;

    ServiceProvider() {
        // compile-time checks
        static_assert(std::is_enum<typename Derived::ServiceName>::value, "Derived class must define an enum ServiceName");
        static_assert(SIZE > 0, "Size of ServiceProvider must be greater than 0.");

        // Crear el proxy para exponer los servicios
        proxy = new ServiceAccessor(static_cast<Derived*>(this));
    }

    // Método para registrar servicios
    void registerService(std::size_t variableIndex, int (Derived::*func)()) {
        static_assert(std::is_integral<std::size_t>::value, "Index must be an unsigned integer.");
        if (variableIndex >= SIZE) {
            return; //TODO: Manejo correcto del errores
        }        

        serviceArray[static_cast<std::size_t>(variableIndex)] = [func](Derived* instance) {
            return (instance->*func)();
        };
    }

     // Definición de ServiceAccessor
    class ServiceAccessor {
    protected:
        Derived* derived;
    public:
        ServiceAccessor(Derived* derived) : derived(derived) {};

        // Invocar servicio por enum
        int invokeService(typename Derived::ServiceName service) {
            //static_assert(service != Derived::ServiceName::Count, "Cannot invoke 'Count' as a service");

            auto idx = static_cast<std::size_t>(service);
            
            // Verificamos que el servicio está registrado
            if (idx >= SIZE) {
                //Serial.println("Error: Invalid service type");
                return -1; //TODO: Manejo correcto del errores
            }
            if (!derived->serviceArray[idx]) {
                //Serial.println("Error: Service not registered");
                return -1;  //TODO: Manejo correcto del errores
            }
            
            // Invocar el servicio registrado
            return derived->serviceArray[idx](derived);  
        }
    };

    // Obtener el proxy de servicio
    ServiceAccessor* getServiceProxy() {
        return proxy;
    }

private:
    ServiceAccessor* proxy;
};


/*
// src/core/interfaces/ServiceProvider.hpp



template<typename Derived>
class ServiceProvider {

protected:
    std::array<std::function<int(Derived*)>, static_cast<std::size_t>(Derived::ServiceName::Count)> serviceArray;
    ServiceAccessor* proxy;

public:
    ServiceProvider() {
        // Verificamos que Derived tiene un enum ServiceName
        static_assert(std::is_enum<typename Derived::ServiceName>::value, 
                      "Derived class must define an enum ServiceName");

        // Verificamos que el enum tiene al menos un valor y termina con Count
        static_assert(static_cast<std::size_t>(Derived::ServiceName::Count) > 0, 
                      "Enum ServiceName must contain at least one service and end with Count");

        

        // Crear el proxy para exponer los servicios
        proxy = new ServiceAccessor(static_cast<Derived*>(this));
    }

    // Método para registrar servicios
    void registerService(typename Derived::ServiceName service, int (Derived::*func)()) {
        static_assert(service != Derived::ServiceName::Count,  "Cannot register 'Count' as a service");
        
        serviceArray[static_cast<std::size_t>(service)] = [func](Derived* instance) {
            return (instance->*func)();
        };
    }

    // Obtener el proxy de servicio
    ServiceProxy* getServiceProxy() {
        return proxy;
    }

    // Proxy para los servicios
 
    class ServiceAccessor{
    protected:
        Derived* derived;

    public:
        ServiceAccessor(Derived* derived) : derived(derived) {}

        // Invocar servicio por enum
        int invokeService(typename Derived::ServiceName service) {
            static_assert(service != Derived::ServiceName::Count,
                          "Cannot invoke 'Count' as a service");

            auto idx = static_cast<std::size_t>(service);
            
            // Verificamos que el servicio está registrado
            if (idx >= static_cast<std::size_t>(Derived::ServiceName::Count)) {
                Serial.println("Error: Invalid service type");
                return -1; //TODO: manejar mejor
            }
            if (!derived->serviceArray[idx]) {
                Serial.println("Error: Service not registered");
                return -1;// TODO: manejar mejor
            }
            
            // Invocar el servicio registrado
            return derived->serviceArray[idx](derived);  
        }
    };

};
*/