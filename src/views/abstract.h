#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <functional>
#include "../managers/typeName.h"

class AppManager;

class IView {
public:
    IView(AppManager& manager) : manager(manager) {}
    ~IView() = default;

    virtual void render(int el) = 0;
    virtual void update() = 0;
    virtual void init() = 0;
protected:
    AppManager& manager;
};

using ViewFactory = std::function<std::unique_ptr<IView>(AppManager&)>;

class ViewRegistry {
public:
    static ViewRegistry& instance() {
        static ViewRegistry registry;
        return registry;
    }

    void registerView(const std::string& name, ViewFactory factory) {
        factories[name] = std::move(factory);
    }

    const std::unordered_map<std::string, ViewFactory>& getFactories() const {
        return factories;
    }

private:
    std::unordered_map<std::string, ViewFactory> factories;
};

#define REGISTER_VIEW(TYPE) \
namespace { \
    struct TYPE##Registrar { \
        TYPE##Registrar() { \
            ViewRegistry::instance().registerView(#TYPE, [](AppManager& mgr) -> std::unique_ptr<IView> { \
                return std::make_unique<TYPE>(mgr); \
            }); \
        } \
    }; \
    static TYPE##Registrar global_##TYPE##Registrar; \
}\
DEFINE_TYPE_NAME(TYPE)
