#include <array>
#include <functional>
#include "Concepts.h"

#define REGISTER_SERVICE(ServiceEnum, Method) \
    registerService(ServiceEnum, &std::remove_reference<decltype(*this)>::type::Method)

/**
 * @file MethodRegistry.cpp
 * @brief Registers and manages service methods for a Peripheral.
 * 
 * This class allows the registration of service methods, and provides functionality to invoke them by index.
 * 
 * @tparam NumServices The number of services that can be registered.
 */
template<std::size_t NumServices>
class MethodRegistry {
public:
    /**
     * @brief Type alias for a service function.
     */
    using ServiceFunction = void (*)();

    /**
    * @brief Constructor that initializes the service array to nullptr.
    */
    constexpr MethodRegistry() : services_{} {
        static_assert(NumServices > 0, "The number of services must be greater than 0");
    }

    /**
     * @brief Registers a service method.
     * 
     * @tparam Derived The derived class type.
     * @param idx The index to register the service.
     * @param func Pointer to the service method.
     * @param instance Reference to the instance that will call the method.
     */
    template <typename Derived>
    constexpr void registerService(std::size_t idx, void (Derived::*func)(), Derived& instance) const {
        if (idx >= NumServices) {
            //throw std::out_of_range("Index out of range for registering the service");
            //TODO: Manejo de errores
        }
        services_[idx] = [func, &instance]() { (instance.*func)(); };
    }

    /**
     * @brief Invokes a service by index.
     * 
     * @param idx The index of the service to invoke.
     */
    void invoke(std::size_t idx) const {
        if (idx >= NumServices || !services_[idx]) {
            //TODO: Manejo de errores
            //throw std::out_of_range("Index out of range or service not registered");
        }
        services_[idx]();
    }

    /**
     * @brief Invokes a specific service by enum.
     * 
     * @tparam ServiceEnum The enum type representing the services.
     * @param service The enum value representing the service to invoke.
     */
    template <typename ServiceEnum>
    void invoke(ServiceEnum service) const {
        static_assert(IsEnum<ServiceEnum>, "ServiceEnum must be an enum.");
        invoke(static_cast<std::size_t>(service));
    }

private:
    /**
     * @brief Array storing service functions.
     */
    mutable std::array<std::function<void()>, NumServices> services_;
};