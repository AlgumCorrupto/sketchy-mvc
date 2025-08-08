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
       view->init();
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
