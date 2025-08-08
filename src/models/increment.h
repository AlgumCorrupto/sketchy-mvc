#pragma once

#include "abstract.h"

class IncrementModel : public IModel {
public:
    IncrementModel() : count(0) {}
    int increment() { return count++; }
    int decrement() { return count--; }
    int getCount() { return count; }
private:
    int count;
};
REGISTER_MODEL(IncrementModel)
