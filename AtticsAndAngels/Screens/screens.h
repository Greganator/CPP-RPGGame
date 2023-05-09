#pragma once
#include "raylib.h"
#include "UIHelpers.h"
#include "../Vault.h"
#include <string>

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING, TEAMCREATE } GameScreen;

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern GameScreen currentScreen;
extern Music music;

namespace Screens
{
	namespace Scenes
	{
        
		//----------------------------------------------------------------------------------
		// Logo Screen Functions Declaration
		//----------------------------------------------------------------------------------
		void InitLogoScreen();
		void UpdateLogoScreen();
		void DrawLogoScreen();
		void UnloadLogoScreen();
		int FinishLogoScreen();

		//----------------------------------------------------------------------------------
		// Title Screen Functions Declaration
		//----------------------------------------------------------------------------------
		void InitTitleScreen();
		void UpdateTitleScreen();
		void DrawTitleScreen();
		void UnloadTitleScreen();
		int FinishTitleScreen();

		//----------------------------------------------------------------------------------
		// Options Screen Functions Declaration
		//----------------------------------------------------------------------------------
		void InitOptionsScreen();
		void UpdateOptionsScreen();
		void DrawOptionsScreen();
		void UnloadOptionsScreen();
		int FinishOptionsScreen();

		//----------------------------------------------------------------------------------
		// Gameplay Screen Functions Declaration
		//----------------------------------------------------------------------------------
        namespace Gameplay
        {
            void InitGameplayScreen();
            void UpdateGameplayScreen();
            void DrawGameplayScreen();
            void UnloadGameplayScreen();
            int FinishGameplayScreen();
        }

		//----------------------------------------------------------------------------------
		// Ending Screen Functions Declaration
		//----------------------------------------------------------------------------------
        namespace Ending
        {
            void InitEndingScreen();
            void UpdateEndingScreen();
            void DrawEndingScreen();
            void UnloadEndingScreen();
            int FinishEndingScreen();
        }

        //----------------------------------------------------------------------------------
        // Team Creation Screen Functions Declaration
        //----------------------------------------------------------------------------------
        void InitCreateScreen();
        void UpdateCreateScreen();
        void DrawCreateScreen();
        void UnloadCreateScreen();
        int FinishCreateScreen();
	}
	//----------------------------------------------------------------------------------
	// Helper Functions Declaration
	//----------------------------------------------------------------------------------
	inline void InitScreen(GameScreen screen)
	{
		switch (screen)
		{
        case LOGO: Scenes::InitLogoScreen(); break;
		case TITLE: Scenes::InitTitleScreen(); break;
		case GAMEPLAY: Scenes::Gameplay::InitGameplayScreen(); break;
		case ENDING: Scenes::Ending::InitEndingScreen(); break;
        case TEAMCREATE: Scenes::InitCreateScreen(); break;
		default: break;
		}
	}
	inline void DrawScreen(GameScreen screen)
	{
		switch (screen)
		{
		case LOGO: Scenes::DrawLogoScreen(); break;
		case TITLE: Scenes::DrawTitleScreen(); break;
		case OPTIONS: Scenes::DrawOptionsScreen(); break;
		case GAMEPLAY: Scenes::Gameplay::DrawGameplayScreen(); break;
		case ENDING: Scenes::Ending::DrawEndingScreen(); break;
        case TEAMCREATE: Scenes::DrawCreateScreen(); break;
		default: break;
		}
	}
	inline void UnloadScreen(GameScreen screen)
	{
		switch (screen)
		{
		case LOGO: Scenes::UnloadLogoScreen(); break;
		case TITLE: Scenes::UnloadTitleScreen(); break;
		case GAMEPLAY: Scenes::Gameplay::UnloadGameplayScreen(); break;
		case ENDING: Scenes::Ending::UnloadEndingScreen(); break;
        case TEAMCREATE: Scenes::UnloadCreateScreen(); break;
		default: break;
		}
	}

    // Required variables to manage screen transitions (fade-in, fade-out)
    inline float transAlpha = 0.0f;
    inline bool onTransition = false;
    inline bool transFadeOut = false;
    inline int transFromScreen = -1;
    inline int transToScreen = -1;

    inline void TransitionToScreen(GameScreen screen)
    {
        onTransition = true;
        transFadeOut = false;
        transFromScreen = currentScreen;
        transToScreen = screen;
        transAlpha = 0.0f;
    }

    // Update transition effect (fade-in, fade-out)
    inline void UpdateTransition()
    {
        if (!transFadeOut)
        {
            transAlpha += 0.05f;

            // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
            // For that reason we compare against 1.01f, to avoid last frame loading stop
            if (transAlpha > 1.01f)
            {
                transAlpha = 1.0f;

                // Unload current screen
                Screens::UnloadScreen(static_cast<GameScreen>(transFromScreen));

                // Load next screen
                Screens::InitScreen(static_cast<GameScreen>(transToScreen));

                currentScreen = static_cast<GameScreen>(transToScreen);

                // Activate fade out effect to next loaded screen
                transFadeOut = true;
            }
        }
        else  // Transition fade out logic
        {
            transAlpha -= 0.02f;

            if (transAlpha < -0.01f)
            {
                transAlpha = 0.0f;
                transFadeOut = false;
                onTransition = false;
                transFromScreen = -1;
                transToScreen = -1;
            }
        }
    }

    // Draw transition effect (full-screen rectangle)
    inline void DrawTransition()
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
    }

    // Update and draw game frame
    inline void UpdateDrawFrame()
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

        if (!onTransition)
        {
            switch (currentScreen)
            {
            case LOGO:
            {
                Scenes::UpdateLogoScreen();

                if (Scenes::FinishLogoScreen()) TransitionToScreen(TITLE);

            } break;
            case TITLE:
            {
                Scenes::UpdateTitleScreen();

                if (Scenes::FinishTitleScreen() == 1) TransitionToScreen(OPTIONS);
                else if (Scenes::FinishTitleScreen() == 2) TransitionToScreen(TEAMCREATE);

            } break;
            case OPTIONS:
            {
                Scenes::UpdateOptionsScreen();

                if (Scenes::FinishOptionsScreen()) TransitionToScreen(TITLE);

            } break;
            case GAMEPLAY:
            {
                Scenes::Gameplay::UpdateGameplayScreen();

                if (Scenes::Gameplay::FinishGameplayScreen() == 1) TransitionToScreen(ENDING);

            } break;
            case ENDING:
            {
                Scenes::Ending::UpdateEndingScreen();

                if (Scenes::Ending::FinishEndingScreen() == 1) TransitionToScreen(TITLE);

            } break;
            case TEAMCREATE:
            {
                Scenes::UpdateCreateScreen();

                if (Scenes::FinishCreateScreen() == 1) TransitionToScreen(GAMEPLAY);
            }
            default: break;
            }
        }
        else UpdateTransition();    // Update transition (fade-in, fade-out)
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawScreen(currentScreen);

        // Draw full screen rectangle in front of everything
        if (onTransition) DrawTransition();

        //DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

}
