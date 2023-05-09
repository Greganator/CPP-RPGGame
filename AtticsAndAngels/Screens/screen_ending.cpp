#include "screens.h"

namespace Screens
{
    //----------------------------------------------------------------------------------
    // Module Variables Definition (local)
    //----------------------------------------------------------------------------------
    static int framesCounter = 0;
    static int finishScreen = 0;

    namespace Scenes::Ending
    {

        bool PlayerVictory;

        Vault::Vault* v;
        Team::PlayerTeam* team;

        Texture2D background;

        Vector2 textpoint;

        // Ending Screen Initialization logic
        void InitEndingScreen()
        {
            v = Vault::Vault::GetVault();
            team = v->GetTeam();

            PlayerVictory = !team->AreAllCharacterDead();

            textpoint = UI::GetSceenPosFromPrecentage(.5, .2);

            if (PlayerVictory)
            {
                background = UI::LoadTextureFromResources("resources/Art/Backgrounds/Cursed_Kingdoms_-_portal_active.png");
                UI::LoadBackgroundMusic("resources/Audio/Victory.ogg", music);
                team->LevelUpTeam();
                v->SaveTeam();
            }
            else
            {
                background = UI::LoadTextureFromResources("resources/Art/Backgrounds/Cursed_Kingdoms_-_portal_inactive.png");
                UI::LoadBackgroundMusic("resources/Audio/Loss.ogg", music);
                v->ClearTeam();
            }

            // TODO: Initialize ENDING screen variables here!
            framesCounter = 0;
            finishScreen = 0;
        }

        // Ending Screen Update logic
        void UpdateEndingScreen()
        {
            // TODO: Update ENDING screen variables here!

            // Press enter or tap to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                finishScreen = 1;
            }
        }

        // Ending Screen Draw logic
        void DrawEndingScreen()
        {
         
            UI::DrawBackgroundTexture(background, WHITE);

            if (PlayerVictory)
            {
                DrawText("Victory", textpoint.x-130, textpoint.y-200 , 80, GOLD);
                DrawText("Congragulations you may continue with this team at any time", textpoint.x - 600, textpoint.y + 700, 40, GOLD);
            }
            else
            {
                DrawText("YOUR JOURNEY ENDS", textpoint.x - 300, textpoint.y, 60, DARKPURPLE);
                DrawText("Click anywhere to return to the main menu", textpoint.x - 500, textpoint.y+700, 40, RED);
            }
        }

        // Ending Screen Unload logic
        void UnloadEndingScreen()
        {
            v = nullptr;
            team = nullptr;
            UnloadTexture(background);
        }

        // Ending Screen should finish?
        int FinishEndingScreen()
        {
            return finishScreen;
        }
    }
}