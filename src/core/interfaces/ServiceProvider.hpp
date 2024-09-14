#pragma once
#include <array>         // Para std::array
#include <functional>    // Para std::function
#include <optional>      // Para std::optional
#include <cstddef>       // Para std::size_t
#include <type_traits>   // Para std::is_base_of, std::is_enum

#define REGISTER_SERVICE(serviceName, method) registerService(static_cast<std::size_t>(serviceName), method)

template<typename Derived, std::size_t NumServices>
class ServiceProvider {
protected:
    // Array opcional para almacenar las funciones de servicio
    ///TODO: ver que es esto de optional
    std::array<std::optional<std::function<int(Derived*)>>, NumServices> serviceArray;

public:
    // Definición de ServiceApi
    class ServiceApi {
    private:
        Derived* derived;
    public:
        ServiceApi(Derived* derived) : derived(derived) {}

        // Invocar servicio por índice (size_t)
        int invokeService(std::size_t idx) {
            if (hasService(idx)) {
                // Invocar el servicio registrado
                return (*derived->serviceArray[idx])(derived);
            } else {
                // Manejo de error: servicio no registrado o índice fuera de rango
                return -1; // Retorna un código de error si el índice es inválido
            }
        }

        // Verificar si un servicio está registrado
        bool hasService(std::size_t idx) const {
            return 0 <= idx && idx < derived->serviceArray.size() && derived->serviceArray[idx].has_value();
        }
    };

    // API para exponer los servicios
    ServiceApi api;

    // Constructor
    ServiceProvider() : api(static_cast<Derived*>(this)) {
        // Verificación en tiempo de compilación: Derived debe heredar de ServiceProvider
        static_assert(std::is_base_of<ServiceProvider, Derived>::value, "Derived must inherit from ServiceProvider");

        // Verificación en tiempo de compilación: Derived debe tener un enum llamado ServiceName
        static_assert(std::is_enum<typename Derived::ServiceName>::value, "Derived must define an enum ServiceName");
    }

    // Método para registrar servicios
    void registerService(std::size_t idx, int (Derived::*func)()) {
        if (idx < NumServices) {
            serviceArray[idx] = [func](Derived* instance) {
                return (instance->*func)();
            };
        }
    }

    // Obtener la API de servicios
    ServiceApi* getServiceApi() {
        return &api;
    }
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