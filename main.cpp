#include "raylib.h"
#include "imgui_impl_raylib.h"

#include "model.h"
#include "controller.h"
#include "view.h"
#include "manager.h"

int main(int argc, char const** argv)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = Vector3{ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                              // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;           // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Imgui initialization
    //--------------------------------------------------------------------------------------
    ImGui::CreateContext(nullptr);
    ImGui::StyleColorsDark(nullptr);
    ImGui_ImplRaylib_Init();
    // Create textures

    // Build and load the texture atlas into a texture
    // (In the examples/ app this is usually done within the ImGui_ImplXXX_Init() function from one of the demo Renderer)
    struct ImGuiIO* io;
    io = &ImGui::GetIO();
    unsigned char* pixels = nullptr;

    int width = screenWidth;
    int height = screenHeight;

    io->Fonts->TexDesiredWidth = 2048;
    io->Fonts->TexGlyphPadding = 1;
    io->Fonts->Flags |= ImFontAtlasFlags_NoPowerOfTwoHeight;

    io->Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, nullptr);

    // At this point you've got the texture data and you need to upload that your your graphic system:
    // After we have created the texture, store its pointer/identifier (_in whichever format your engine uses_) in 'io.Fonts->TexID'.
    // This will be passed back to your via the renderer. Basically ImTextureID == void*. Read FAQ for details about ImTextureID.
    Image image = {};
    image.data = pixels;
    image.width = width;
    image.height = height;
    image.mipmaps = 1;
    image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    Texture2D texture = LoadTextureFromImage(image);
    io->Fonts->TexID = (void*)(&texture.id);
    //--------------------------------------------------------------------------------------
    
    // MVC Initialization
    //--------------------------------------------------------------------------------------
    AppManager app;
    auto& view = app.getView<IncrementView>();

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_ORBITAL);          // Update camera

        // Imgui start drawing
        //--------------------------------------------------------------------------------------
        ImGui_ImplRaylib_NewFrame();
        ImGui_ImplRaylib_ProcessEvent();
        ImGui::NewFrame();
        //--------------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            // Imgui widgets
            //--------------------------------------------------------------------------------------
  
            view.render();
            //--------------------------------------------------------------------------------------
          
            // Imgui end drawing
            //--------------------------------------------------------------------------------------
            ImGui::Render();
            raylib_render_imgui(ImGui::GetDrawData());
            //--------------------------------------------------------------------------------------


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
