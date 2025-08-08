#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
class AppManager;

class IController {
public:
    IController(AppManager& manager) : manager(manager) {}
    virtual ~IController() = default;
    virtual void init() = 0;
protected:
    AppManager& manager;
};

using ControllerFactory = std::function<std::unique_ptr<IController>(AppManager&)>;

class ControllerRegistry {
public:
    static ControllerRegistry& instance() {
        static ControllerRegistry registry;
        return registry;
    }

    void registerController(const std::string& name, ControllerFactory factory) {
        factories[name] = factory;
    }

    const std::unordered_map<std::string, ControllerFactory>& getFactories() const {
        return factories;
    }

private:
    std::unordered_map<std::string, ControllerFactory> factories;
};

#define REGISTER_CONTROLLER(TYPE) \
namespace { \
    struct TYPE##Registrar { \
        TYPE##Registrar() { \
            ControllerRegistry::instance().registerController(#TYPE, [](AppManager& mgr) { \
                return std::make_unique<TYPE>(mgr); \
            }); \
        } \
    }; \
    static TYPE##Registrar global_##TYPE##Registrar; \
}\
DEFINE_TYPE_NAME(TYPE)
