#include "screens.h"
#include "../JsonSaveLoad.h"
namespace Screens
{
    //----------------------------------------------------------------------------------
    // Module Variables Definition (local)
    //----------------------------------------------------------------------------------
    static int framesCounter = 0;
    static int finishScreen = 0;

    //----------------------------------------------------------------------------------
    // Title Screen Functions Definition
    //----------------------------------------------------------------------------------
    namespace Scenes
    {
        bool playButtonPressed = false;
        bool continueButtonPressed = false;
        bool optionsButtonPressed = false;

        Vector2 anchor01 = { 0,0 };

        Texture2D backgorund;

        // Title Screen Initialization logic
        void InitTitleScreen()
        {
            UI::LoadBackgroundMusic("resources/Audio/TitleScreen.ogg", music);

            backgorund = UI::LoadTextureFromResources("resources/Art/TitleScreen.png");

            anchor01 = UI::GetSceenPosFromPrecentage(.06f, .9f );

            framesCounter = 0;
            finishScreen = 0;
        }

        // Title Screen Update logic
        void UpdateTitleScreen()
        {

            if (playButtonPressed)
            {
                Vault::Vault::GetVault()->ClearTeam();
                finishScreen = 2;   // TEAMCREATE
            }
            if (optionsButtonPressed)
            {
                finishScreen = 1;   // OPTIONS
            }
            if (continueButtonPressed)
            {
                Vault::Vault::GetVault()->LoadTeamSave();
                finishScreen = 2;             
            }
        }

        // Title Screen Draw logic
        void DrawTitleScreen()
        {
            UI::DrawBackgroundTexture(backgorund, WHITE);
            DrawTextEx(GuiGetFont(), "Attics & Angels", Vector2{ 20, 10 }, GuiGetFont().baseSize * 4, 4, RED);
            playButtonPressed = GuiButton(Rectangle{ anchor01.x, anchor01.y, 120, 40 }, "New Game");
            if (SaveLoad::JsonSaveLoad::DoesSaveExist())
            {
                continueButtonPressed = GuiButton(Rectangle{ anchor01.x + 200, anchor01.y, 120, 40 }, "Continue");
            }
            //optionsButtonPressed = GuiButton(Rectangle{ anchor01.x + 400, anchor01.y, 120, 40 }, "Options"); Options are a lie disable button
        }

        // Title Screen Unload logic
        void UnloadTitleScreen()
        {
            UnloadTexture(backgorund);
        }

        // Title Screen should finish?
        int FinishTitleScreen()
        {
            return finishScreen;
        }
    }
}