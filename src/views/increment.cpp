#include "increment.h"
#include "raylib.h"
#include "imgui_impl_raylib.h"
#include "../manager.h"
#include "../controller.h"
void IncrementView::render() {
    auto& controller = manager.getController<IncrementController>();
    bool p_open = true;
    ImGui::SetNextWindowPos(ImVec2(0,0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(),GetScreenHeight()));
    ImGui::Begin("Increment");
    ImGui::Text("Count: %d", controller.getValue());
    if (ImGui::Button("Increment")) controller.increment();
    if (ImGui::Button("Decrement")) controller.decrement();
    ImGui::End();
}
