#include "appManager.h"

#include <iostream>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>

#include "../views/abstract.h"
#include "../models/abstract.h"
#include "../controllers/abstract.h"

void AppManager::initViews() {
   for (auto& [name, factory] : ViewRegistry::instance().getFactories()) {
       auto view = factory(*this);
       views[name] = std::move(view);
   }
}
void AppManager::initModels() {
   for (auto& [name, factory] : ModelRegistry::instance().getFactories()) {
       auto model = factory();
       models[name] = std::move(model);
   }
}
void AppManager::initControllers() {
    for (auto& [name, factory] : ControllerRegistry::instance().getFactories()) {
        auto controller = factory(*this);
        controller->init();
        controllers[name] = std::move(controller);
    }
}
//template<typename T>
//T& AppManager::getModel() {
//    auto it = models.find(typeName<T>());
//    if (it == models.end()) {
//        throw std::runtime_error("Model not found: " + typeName<T>());
//    }
//    return *static_cast<T*>(it->second.get());
//}
//
//template<typename T>
//T& AppManager::getController() {
//    auto it = controllers.find(typeName<T>());
//    if (it == controllers.end()) {
//        throw std::runtime_error("Controller not found: " + typeName<T>());
//    }
//    return *static_cast<T*>(it->second.get());
//}
//
//template<typename T>
//T& AppManager::getView() {
//    auto it = views.find(typeName<T>());
//    if (it == views.end()) {
//        throw std::runtime_error("View not found: " + typeName<T>());
//    }
//    return *static_cast<T*>(it->second.get());
//}
