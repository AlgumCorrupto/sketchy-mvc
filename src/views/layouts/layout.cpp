#include "layout.h"
#include "raylib.h"
#include "imgui_impl_raylib.h"
#include "../../manager.h"
#include <iostream>
#include "../../controller.h"

void LayoutView::render(int el) {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* handle open */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* handle save */ }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) { /* handle exit */ }
            ImGui::EndMenu();
        }
    
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* undo */ }
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) { /* disabled item */ }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    renderCurr(el);
}

void LayoutView::renderCurr(int el) {
    manager.getCurrentView().render(el);
}
