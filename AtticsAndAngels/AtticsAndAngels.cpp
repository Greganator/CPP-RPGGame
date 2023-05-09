// AtticsAndAngels.cpp : Defines the entry point for the application.
//

#define RAYGUI_IMPLEMENTATION
#include "Screens/screens.h"
#include "Vault.h"
#include "JsonSaveLoad.h"

#include "thirdparty/nlohmann/json.hpp"
using json = nlohmann::json;

// TODO: Reference additional headers your program requires here.

    //----------------------------------------------------------------------------------
    // Local Variables Definition (local to this module)
    //----------------------------------------------------------------------------------
const int screenWidth = 1920;
const int screenHeight = 1080;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
void ChangeToScreen(GameScreen screen);     // Change to screen, no transition effect

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
GameScreen currentScreen = GameScreen::LOGO;
Music music = { 0 };

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
void ChangeToScreen(GameScreen screen)
{
    // Unload current screen
    Screens::UnloadScreen(currentScreen);

    // Init next screen
    Screens::InitScreen(screen);

    currentScreen = screen;
}

int main()
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "A&A");

    InitAudioDevice();      // Initialize audio device

    // Load global data (assets that must be available in all screens, i.e. font)
    GuiLoadStyle("resources/ashes.rgs");
    music = LoadMusicStream("resources/Audio/ambient.ogg");

    SetMusicVolume(music, .4f);
    PlayMusicStream(music);

    // Setup and init first screen
    currentScreen = LOGO;
    Screens::InitScreen(currentScreen);

   const Vault::Vault* const v = v->GetVault();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Screens::UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    Screens::UnloadScreen(currentScreen);

    // Unload global data loaded
    UnloadMusicStream(music);

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

