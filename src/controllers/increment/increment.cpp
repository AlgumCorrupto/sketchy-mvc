#include "../../manager.h"
#include "increment.h"
void IncrementController::increment() {incModel->increment();}
void IncrementController::decrement() {incModel->decrement();}
int  IncrementController::getValue() {return incModel->getCount();}

void IncrementController::init() {incModel = &manager.getModel<IncrementModel>();}

