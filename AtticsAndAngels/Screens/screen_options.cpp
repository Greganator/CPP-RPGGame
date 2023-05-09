#include "screens.h"

namespace Screens
{
    //----------------------------------------------------------------------------------
    // Module Variables Definition (local)
    //----------------------------------------------------------------------------------
    static int framesCounter = 0;
    static int finishScreen = 0;

    namespace Scenes
    {
        // Options Screen Initialization logic
        void InitOptionsScreen()
        {
            // TODO: Initialize OPTIONS screen variables here!
            framesCounter = 0;
            finishScreen = 0;
        }

        // Options Screen Update logic
        void UpdateOptionsScreen()
        {
            // TODO: Update OPTIONS screen variables here!
        }

        // Options Screen Draw logic
        void DrawOptionsScreen()
        {
            // TODO: Draw OPTIONS screen here!
        }

        // Options Screen Unload logic
        void UnloadOptionsScreen()
        {
            // TODO: Unload OPTIONS screen variables here!
        }

        // Options Screen should finish?
        int FinishOptionsScreen()
        {
            return finishScreen;
        }
    }
}