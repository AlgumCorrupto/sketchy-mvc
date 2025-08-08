#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include "../managers/typeName.h"

class IModel {
public:
    ~IModel() = default;
};

using ModelFactory = std::function<std::unique_ptr<IModel>()>; 

class ModelRegistry {
public:
    static ModelRegistry& instance() {
        static ModelRegistry registry;
        return registry;
    }

    void registerModel(const std::string& name, ModelFactory factory) {
        factories[name] = std::move(factory);
    }

    std::unique_ptr<IModel> create(const std::string& name) const {
        auto it = factories.find(name);
        if (it != factories.end()) {
            return (it->second)();
        }
        return nullptr;
    }

    const std::unordered_map<std::string, ModelFactory>& getFactories() const {
        return factories;
    }

private:
    std::unordered_map<std::string, ModelFactory> factories;
};

#define REGISTER_MODEL(TYPE)                               \
    namespace {                                            \
        struct TYPE##ModelRegistrar {                      \
            TYPE##ModelRegistrar() {                       \
                ModelRegistry::instance().registerModel(   \
                    #TYPE,                                 \
                    []() -> std::unique_ptr<IModel> {     \
                        return std::make_unique<TYPE>();  \
                    }                                       \
                );                                         \
            }                                               \
        };                                                  \
        static TYPE##ModelRegistrar global_##TYPE##ModelRegistrar; \
    } \
    DEFINE_TYPE_NAME(TYPE)

