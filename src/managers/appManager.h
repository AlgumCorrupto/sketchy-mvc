#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>

#include "../views/abstract.h"
#include "../models/abstract.h"
#include "../controllers/abstract.h"
#include "typeName.h"

class AppManager {
public:
    AppManager() {
        initModels();
        initControllers();
        initViews();
    }

    // Create and store all vies registered
    void initViews();

    // Create and store all models registered
    void initModels();

    // Create and store all controllers registered
    void initControllers();

    // Access model by type
    template<typename T>
    T& getModel();

    // Access controller by type
    template<typename T>
    T& getController();

    template<typename T>
    T& getView();

private:
    // Helper for getting type name as string (using RTTI)
    //template<typename T>
    //static std::string typeName() {
    //    return typeid(T).name();
    //}

    std::unordered_map<std::string, std::unique_ptr<IModel>> models;
    std::unordered_map<std::string, std::unique_ptr<IController>> controllers;
    std::unordered_map<std::string, std::unique_ptr<IView>> views;
};

template<typename T>
T& AppManager::getModel() {
    auto it = models.find(TypeName<T>::get());
    if (it == models.end()) {
        throw std::runtime_error("Model not found: " + TypeName<T>::get());
    }
    return *static_cast<T*>(it->second.get());
}

template<typename T>
T& AppManager::getController() {
    auto it = controllers.find(TypeName<T>::get());
    if (it == controllers.end()) {
        throw std::runtime_error("Controller not found: " + TypeName<T>::get());
    }
    return *static_cast<T*>(it->second.get());
}

template<typename T>
T& AppManager::getView() {
    auto it = views.find(TypeName<T>::get());
    if (it == views.end()) {
        throw std::runtime_error("View not found: " + TypeName<T>::get());
    }
    return *static_cast<T*>(it->second.get());
}
