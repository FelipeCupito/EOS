#include <tuple>
#include <type_traits>
#include "MethodRegistry.cpp"
#include "ExposedVars.cpp"
#include "Concepts.h"
#include "EventEmitter.cpp"
#include "VarViewer.cpp"

/**
 * @file Peripheral.cpp
 * @brief A base class that handles different communication strategies for peripherals.
 * 
 * This class combines various communication interfaces, such as ExposedVars, MethodRegistry, 
 * and EventEmitter, enabling peripherals to expose variables, register methods, and emit events.
 * 
 * @tparam Derived The derived class using this base Peripheral class.
 * @tparam CommInterfaces A variadic list of communication interfaces.
 */
template <typename Derived, typename... CommInterfaces>
class Peripheral {
    static_assert(unique_types<CommInterfaces...>::value, 
                  "Error: Duplicate communication interfaces detected.");

public:
    Peripheral() : interfaces_{CommInterfaces()...} {};
    /******************** Event Emission ***********************************/
    /**
     * @brief Emits an event from the derived class.
     * This method is only available if the derived class has an enum called EventName.
     * 
     * @tparam EventEnum The enum type representing the event.
     * @param event The enum value representing the event to emit.
     */
    template <typename EventEnum>
    requires HasCommInterfaces<EventEmitter, CommInterfaces...>
    void emit(EventEnum event) const {
        static_assert(HasEventTypeEnum<Derived>, "Error: Derived class must have an enum named 'EventName'");
        
        //TODO: Implementar
    }
    
    /******************** ExposedVars ***********************************/
    /**
     * @brief Registers a shared variable for a given Derived instance.
     * 
     * @tparam VariableEnum The enum representing the variable.
     * @tparam VarType The type of the variable to register.
     * @param varEnum The enum value representing the variable.
     * @param varPtr A pointer to the variable.
     */
    template <typename VariableEnum, typename VarType>
    requires HasCommInterfaces<ExposedVars<static_cast<std::size_t>(VariableEnum::COUNT)>, CommInterfaces...>
    constexpr void registerVariable(VariableEnum varEnum, const VarType* varPtr) {

        auto& exposedVars = getExposedVars();
        exposedVars.template registerVariable(static_cast<std::size_t>(varEnum), varPtr);
    }

    /**
     * @brief Returns a VarViewer that encapsulates access to all shared variables.
     */
    auto getVarViewer() const
    requires HasCommInterfaces<ExposedVars<static_cast<std::size_t>(Derived::VariableName::COUNT)>, CommInterfaces...>
    {
        return VarViewer<Derived, static_cast<std::size_t>(Derived::VariableName::COUNT)>(getExposedVars());
    }

    /******************** MethodRegistry ***********************************/
    /**
     * @brief Registers a service method in the MethodRegistry.
     * 
     * @tparam ServiceEnum The enum type representing the service.
     * @param service The enum value representing the service to register.
     * @param func Pointer to the method to register.
     */
    template <typename ServiceEnum>
    requires HasCommInterfaces<MethodRegistry<static_cast<std::size_t>(ServiceEnum::COUNT)>, CommInterfaces...>
    constexpr void registerService(ServiceEnum service, void (Derived::*func)()) {
        constexpr std::size_t NumServices = static_cast<std::size_t>(ServiceEnum::COUNT);
        auto& provider = getMethodRegistry();
        provider.template registerService(static_cast<std::size_t>(service), func, static_cast<Derived&>(*this));
    }

    /**
     * @brief Returns a ServiceInvoker to invoke services without exposing the entire Peripheral.
     */
    auto getServiceInvoker() const
    requires HasCommInterfaces<MethodRegistry<static_cast<std::size_t>(Derived::ServiceName::COUNT)>, CommInterfaces...>
    {
        return [this](auto serviceEnum) {
            static_assert(std::is_same_v<decltype(serviceEnum), typename Derived::ServiceName>, 
                          "Error: You must use the correct ServiceName enum from the class.");
            getMethodRegistry().invoke(serviceEnum);
        };
        // auto getServiceInvoker() const {
        //     return [this](auto serviceEnum, auto&&... args) -> decltype(auto) {
        //         return getMethodRegistry().invoke(serviceEnum, std::forward<decltype(args)>(args)...);
        //     };
        // }
    }

private:
    /**
     * @brief Tuple to store the communication interfaces.
     */
    std::tuple<CommInterfaces...> interfaces_;

    /**
     * @brief Retrieves the MethodRegistry from the communication interfaces.
     */
    constexpr auto& getMethodRegistry() const
    requires HasCommInterfaces<MethodRegistry<static_cast<std::size_t>(Derived::ServiceName::COUNT)>, CommInterfaces...>
    {
        return std::get<MethodRegistry<static_cast<std::size_t>(Derived::ServiceName::COUNT)>>(interfaces_);
    }

    /**
     * @brief Retrieves the ExposedVars from the communication interfaces.
     */
    constexpr auto& getExposedVars() const
    requires HasCommInterfaces<ExposedVars<static_cast<std::size_t>(Derived::VariableName::COUNT)>, CommInterfaces...>
    {
        return std::get<ExposedVars<static_cast<std::size_t>(Derived::VariableName::COUNT)>>(interfaces_);
    }
};