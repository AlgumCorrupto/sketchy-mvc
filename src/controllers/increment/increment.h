#pragma once

#include "../abstract.h"
#include "../../model.h"

class AppManager;

class IncrementController : public IController {
public:
    IncrementController(AppManager& mgr) : IController(mgr) {}
    void increment();
    void decrement();
    int  getValue();
    void init() override;
private:
    IncrementModel* incModel = nullptr;
};
REGISTER_CONTROLLER(IncrementController)
