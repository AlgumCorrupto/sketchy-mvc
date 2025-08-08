#pragma once

#include "abstract.h"
#include "raylib.h"
#include "imgui_impl_raylib.h"
#include "../manager.h"

class IncrementView : public IView {
public:
    IncrementView(AppManager& mgr) : IView(mgr) {}
    void render() override;
    void update() override {}
};
REGISTER_VIEW(IncrementView)
