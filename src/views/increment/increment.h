#pragma once

#include "../abstract.h"
#include "raylib.h"
#include "imgui_impl_raylib.h"
#include "../../manager.h"
#include "../../models/increment/increment.h"
#include "../../controller.h"

class IncrementView : public IView {
public:
    IncrementView(AppManager& mgr) : IView(mgr) {}
    void render(int el) override;
    void update() override {}
    void init() override;
private:
    IncrementController* controller = nullptr;
};
REGISTER_VIEW(IncrementView)
