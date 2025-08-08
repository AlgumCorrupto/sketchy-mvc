#include "increment.h"
#include "raylib.h"
#include "imgui_impl_raylib.h"
#include "../../manager.h"
#include "../../controller.h"

void IncrementView::render(int el) {
    bool p_open = true;
    ImGui::SetNextWindowPos(ImVec2(0, 19), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(), GetScreenHeight() - 10));
    ImGui::Begin("Increment", nullptr, ImGuiWindowFlags_NoTitleBar);
    
    float window_width = ImGui::GetContentRegionAvail().x;
    float window_height = ImGui::GetContentRegionAvail().y;
    
    float increment_width = ImGui::CalcTextSize("Increment").x;
    float tex_width = ImGui::CalcTextSize("Count: XX").x;  // approximate width for your text
    
    float text_height = ImGui::GetTextLineHeight();
    float button_height = ImGui::GetFrameHeight(); // height of a button
    float spacing = ImGui::GetStyle().ItemSpacing.y;
    
    float content_height = text_height + spacing + button_height + spacing + button_height;
    
    ImGui::SetCursorPosY((window_height - content_height) * 0.5f);
    
    ImGui::SetCursorPosX((window_width - tex_width) * 0.5f);
    ImGui::Text("Count: %d", controller->getValue());
    
    ImGui::SetCursorPosX((window_width - increment_width) * 0.5f);
    if (ImGui::Button("Increment")) controller->increment();
    
    ImGui::SetCursorPosX((window_width - increment_width) * 0.5f);
    if (ImGui::Button("Decrement")) controller->decrement();
    
    ImGui::End();
}

void IncrementView::init() {
    controller = &manager.getController<IncrementController>();
}
