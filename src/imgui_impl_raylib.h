#pragma once

#include "imgui.h"

bool ImGui_ImplRaylib_Init();
void ImGui_ImplRaylib_Shutdown();
void ImGui_ImplRaylib_NewFrame();
bool ImGui_ImplRaylib_ProcessEvent();
void raylib_render_imgui(ImDrawData* draw_data);
