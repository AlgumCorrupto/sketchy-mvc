#pragma once

#include "../abstract.h"
#include "raylib.h"
#include "imgui_impl_raylib.h"

class AppManager;

class LayoutView : public IView {
public:
    LayoutView(AppManager& mgr) : IView(mgr) {}
    void render(int el) override;
    void update() override {}
    void init() override {}
    void renderCurr(int el);
};
REGISTER_VIEW(LayoutView)
