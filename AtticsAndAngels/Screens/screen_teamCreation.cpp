#include "screens.h"
#include <string.h>

namespace Screens
{
	//----------------------------------------------------------------------------------
	// Module Variables Definition (local)
	//----------------------------------------------------------------------------------
	static int framesCounter = 0;
	static int finishScreen = 0;

	namespace Scenes
	{
		//----------------------------------------------------------------------------------
		// Controls Functions Declaration
		//----------------------------------------------------------------------------------
		void AddSTR();
		void AddDEX();
		void AddCON();
		void AddMND();
		void SubSTR();
		void SubDEX();
		void SubCON();
		void SubMND();

		void SetPlayer(const int i);

		void SetClass();
		void SetCharName();
		void UpdateStatBlock();
		void UpdateStatModBlock();

		bool ShouldUpdateClass();

		void SetClassImage();
		void SetWeaponImage();

		// screen_character: controls initialization
		//----------------------------------------------------------------------------------
		// Const text
		const char* GroupBox000Text = "TEAM CREATION";
		const char* nameLabelText = "CHARACTER NAME";
		const char* classLabelText = "CLASS";
		const char* equipmentLabelText = "EQUIPMENT";
		const char* pointsLabelText = "CLASS POINTS";

		const char* classSelectText = "Cleric;Fighter;Wizard";
		const char* gearToggleText = "Gear";
		const char* cpModText = "+";

		std::string DropdownBox035Text = "Cleric;Fighter;Wizard";

		const char* hpLabelText = "HP";
		const char* mpLabelText = "MP";
		const char* intiLabelText = "Initiative";
		const char* strLabelText = "Strength";
		const char* dexLabelText = "Dexterity";
		const char* conLabelText = "Constitution";
		const char* mndLabelText = "Mind";
		const char* addText = "+";
		const char* subText = "-";

		int strlvlText = 0;
		int dexlvlText = 0;
		int conlvlText = 0;
		int mndlvlText = 0;
		int cpRemainingText = 0;
		const char* damageLabel = "Damage";
		const char* weaponLabel = "Weapon";
		int charHPText = 0;
		int charMPText = 0;
		int charINITText = 0;
		std::string charWeaponText = "";
		int charDamageText = 0;

		// Define anchors
		Vector2 centerpoint;            // ANCHOR ID:1
		Vector2 teamcreationAnchor;            // ANCHOR ID:2
		Vector2 characterDisplayAnchor;            // ANCHOR ID:3
		Vector2 infoPannelAnchor;            // ANCHOR ID:4
		Vector2 charStatsAnchor;            // ANCHOR ID:5

		// Define controls variables
		bool charName0EditMode = false;
		char charName0Text[128] = { "" };            // TextBox: charName0
		int classSelect0Active = 0;            // ToggleGroup: classSelect0

		bool charName1EditMode = false;
		char charName1Text[128] = { "" };            // TextBox: charName1
		int classSelect1Active = 0;            // ToggleGroup: classSelect2

		bool charName2EditMode = false;
		char charName2Text[128] = { "" };            // TextBox: charName2
		int classSelect2Active = 0;            // ToggleGroup: classSelect2

		bool charName3EditMode = false;
		char charName3Text[128] = { "" };            // TextBox: charName3
		int classSelect3Active = 0;            // ToggleGroup: classSelect3

		bool DropdownBox035EditMode = false;
		int DropdownBox035Active = 0;            // DropdownBox: DropdownBox035

		Rectangle layoutRecs[64];

		//Character Creation Vars
		Vault::Vault* v;
		Team::PlayerTeam* team;
		Characters::Player* selectedSlot;

		//Images
		Texture2D weaponTexture;
		Texture2D classTexture;

		// Gameplay Screen Initialization logic
		void InitCreateScreen()
		{
			framesCounter = 0;
			finishScreen = 0;

			UI::LoadRandomBackgroundmusic("resources/Audio/CreateScreen/", music);

			// Define anchors
			centerpoint = UI::GetSceenPosFromPrecentage(.5, .5);
			teamcreationAnchor = { centerpoint.x - 408, centerpoint.y - 288 };
			characterDisplayAnchor = { centerpoint.x + 256, centerpoint.y - 288 };
			infoPannelAnchor = { centerpoint.x - 408, centerpoint.y - 48 };
			charStatsAnchor = { centerpoint.x + 256, centerpoint.y - 48 };

			Rectangle layout[] = {
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 48, 528, 40},    // Panel: Panel033
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 88, 528, 40},    // Panel: Panel032
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 128, 528, 40},    // Panel: Panel031
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 168, 528, 40},    // Panel: Panel030
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 0, 528, 553},    // GroupBox: GroupBox000
				Rectangle{teamcreationAnchor.x + 24, teamcreationAnchor.y + 24, 120, 24},    // Label: nameLabel
				Rectangle{teamcreationAnchor.x + 144, teamcreationAnchor.y + 24, 120, 24},    // Label: classLabel
				Rectangle{teamcreationAnchor.x + 264, teamcreationAnchor.y + 24, 96, 24},    // Label: equipmentLabel
				Rectangle{teamcreationAnchor.x + 360, teamcreationAnchor.y + 24, 120, 24},    // Label: pointsLabel
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 40, 528, 12},    // Line: Line005
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 16, 528, 12},    // Line: Line006
				Rectangle{teamcreationAnchor.x + 16, teamcreationAnchor.y + 56, 112, 24},    // TextBox: charName0
				Rectangle{teamcreationAnchor.x + 136, teamcreationAnchor.y + 56, 40, 24},    // ToggleGroup: classSelect0
				Rectangle{teamcreationAnchor.x + 264, teamcreationAnchor.y + 56, 96, 24},    // Toggle: gearToggle0
				Rectangle{teamcreationAnchor.x + 368, teamcreationAnchor.y + 56, 32, 24},    // Toggle: cp0
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 80, 528, 16},    // Line: Line011
				Rectangle{teamcreationAnchor.x + 16, teamcreationAnchor.y + 96, 112, 24},    // TextBox: charName1
				Rectangle{teamcreationAnchor.x + 136, teamcreationAnchor.y + 96, 40, 24},    // ToggleGroup: classSelect2
				Rectangle{teamcreationAnchor.x + 264, teamcreationAnchor.y + 96, 96, 24},    // Toggle: gearToggle1
				Rectangle{teamcreationAnchor.x + 368, teamcreationAnchor.y + 96, 32, 24},    // Toggle: cp1
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 120, 528, 16},    // Line: Line016
				Rectangle{teamcreationAnchor.x + 16, teamcreationAnchor.y + 136, 112, 24},    // TextBox: charName2
				Rectangle{teamcreationAnchor.x + 136, teamcreationAnchor.y + 136, 40, 24},    // ToggleGroup: classSelect2
				Rectangle{teamcreationAnchor.x + 264, teamcreationAnchor.y + 136, 96, 24},    // Toggle: gearToggle2
				Rectangle{teamcreationAnchor.x + 368, teamcreationAnchor.y + 136, 32, 24},    // Toggle: Toggle020
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 160, 528, 16},    // Line: Line021
				Rectangle{teamcreationAnchor.x + 16, teamcreationAnchor.y + 176, 112, 24},    // TextBox: charName3
				Rectangle{teamcreationAnchor.x + 136, teamcreationAnchor.y + 176, 40, 24},    // ToggleGroup: classSelect3
				Rectangle{teamcreationAnchor.x + 264, teamcreationAnchor.y + 176, 96, 24},    // Toggle: gearToggle3
				Rectangle{teamcreationAnchor.x + 368, teamcreationAnchor.y + 176, 32, 24},    // Toggle: cp3
				Rectangle{characterDisplayAnchor.x + -144, characterDisplayAnchor.y + 0, 288, 240},    // Panel: CharacterSpritePanel
				Rectangle{infoPannelAnchor.x + 0, infoPannelAnchor.y + 0, 528, 312},    // Panel: classInfoPannel
				Rectangle{charStatsAnchor.x + -144, charStatsAnchor.y + 0, 288, 312},    // Panel: ClassAssignPointPannel
				Rectangle{teamcreationAnchor.x + 0, teamcreationAnchor.y + 200, 528, 16},    // Line: Line029
				Rectangle{characterDisplayAnchor.x + -96, characterDisplayAnchor.y + 24, 192, 120},    // Panel: selectionSprite
				Rectangle{characterDisplayAnchor.x + -96, characterDisplayAnchor.y + 168, 192, 24},    // DropdownBox: DropdownBox035
				Rectangle{infoPannelAnchor.x + 24, infoPannelAnchor.y + 48, 48, 24},    // Label: hpLabel
				Rectangle{infoPannelAnchor.x + 24, infoPannelAnchor.y + 72, 48, 24},    // Label: Label037
				Rectangle{infoPannelAnchor.x + 24, infoPannelAnchor.y + 96, 48, 24},    // Label: Label038
				Rectangle{charStatsAnchor.x + -120, charStatsAnchor.y + 48, 72, 24},    // Label: strLabel
				Rectangle{charStatsAnchor.x + -120, charStatsAnchor.y + 96, 72, 24},    // Label: dexLabel
				Rectangle{charStatsAnchor.x + -120, charStatsAnchor.y + 144, 72, 24},    // Label: conLabel
				Rectangle{charStatsAnchor.x + -120, charStatsAnchor.y + 192, 72, 24},    // Label: mndLabel
				Rectangle{charStatsAnchor.x + 0, charStatsAnchor.y + 48, 24, 24},    // Button: add0
				Rectangle{charStatsAnchor.x + 0, charStatsAnchor.y + 96, 24, 24},    // Button: add1
				Rectangle{charStatsAnchor.x + 0, charStatsAnchor.y + 192, 24, 24},    // Button: add3
				Rectangle{charStatsAnchor.x + 0, charStatsAnchor.y + 144, 24, 24},    // Button: add2
				Rectangle{charStatsAnchor.x + 24, charStatsAnchor.y + 48, 24, 24},    // Button: sub0
				Rectangle{charStatsAnchor.x + 24, charStatsAnchor.y + 96, 24, 24},    // Button: sub1
				Rectangle{charStatsAnchor.x + 24, charStatsAnchor.y + 144, 24, 24},    // Button: sub2
				Rectangle{charStatsAnchor.x + 24, charStatsAnchor.y + 192, 24, 24},    // Button: sub3
				Rectangle{charStatsAnchor.x + -40, charStatsAnchor.y + 48, 24, 24},    // Label: strlvl
				Rectangle{charStatsAnchor.x + -40, charStatsAnchor.y + 96, 24, 24},    // Label: dexlvl
				Rectangle{charStatsAnchor.x + -40, charStatsAnchor.y + 144, 24, 24},    // Label: conlvl
				Rectangle{charStatsAnchor.x + -40, charStatsAnchor.y + 192, 24, 24},    // Label: mndlvl
				Rectangle{charStatsAnchor.x + 72, charStatsAnchor.y + 24, 24, 24},    // Label: cpRemaining
				Rectangle{infoPannelAnchor.x + 24, infoPannelAnchor.y + 144, 48, 24 },    // Label: Label056
				Rectangle{infoPannelAnchor.x + 24, infoPannelAnchor.y + 120, 48, 24},    // Label: Label057
				Rectangle{infoPannelAnchor.x + 96, infoPannelAnchor.y + 48, 32, 24},    // Label: charHP
				Rectangle{infoPannelAnchor.x + 96, infoPannelAnchor.y + 72, 32, 24},    // Label: charMP
				Rectangle{infoPannelAnchor.x + 96, infoPannelAnchor.y + 96, 32, 24},    // Label: charINIT
				Rectangle{infoPannelAnchor.x + 96, infoPannelAnchor.y + 120, 32, 24},    // Label: charWeapon
				Rectangle{infoPannelAnchor.x + 96, infoPannelAnchor.y + 144, 32, 24},    // Label: charDamage
				Rectangle{centerpoint.x + 0, centerpoint.y + 275, 96, 24} //Exit button
			};


			for (int i = 0; i < (sizeof(layout) / sizeof(layout[0])); ++i)
			{
				layoutRecs[i] = layout[i];
			}

			//Creation setup
			v = Vault::Vault::GetVault();

			if (team == nullptr)
			{
				team = v->CreateTeam();
			}
			else
			{
				team = v->GetTeam();
			}
			selectedSlot = team->GetPlayer(0);

			charName0EditMode = false;
			classSelect0Active = team->Slot0.classID;

			charName1EditMode = false;
			classSelect1Active = team->Slot1.classID;

			charName2EditMode = false;
			classSelect2Active = team->Slot2.classID;

			charName3EditMode = false;
			classSelect3Active = team->Slot3.classID;

			std::strcpy(charName0Text, team->Slot0.name.c_str());
			std::strcpy(charName1Text, team->Slot1.name.c_str());
			std::strcpy(charName2Text, team->Slot2.name.c_str());
			std::strcpy(charName3Text, team->Slot3.name.c_str());

			DropdownBox035EditMode = false;
			DropdownBox035Active = selectedSlot->weaponID;
			DropdownBox035Text = "";

			for (auto& w : v->GetWeaponList())
			{
				DropdownBox035Text += w;
				DropdownBox035Text += ";";
			}

			SetClassImage();
			SetWeaponImage();
		}

		// Gameplay Screen Update logic
		void UpdateCreateScreen()
		{
			SetClass();
			SetCharName();
			UpdateStatBlock();
			UpdateStatModBlock();
		}

		// Gameplay Screen Draw logic
		void DrawCreateScreen()
		{
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			// raygui: controls drawing
			//----------------------------------------------------------------------------------
			// Draw controls
			if (DropdownBox035EditMode) GuiLock();

			GuiPanel(layoutRecs[0], NULL);
			GuiPanel(layoutRecs[1], NULL);
			GuiPanel(layoutRecs[2], NULL);
			GuiPanel(layoutRecs[3], NULL);
			GuiGroupBox(layoutRecs[4], GroupBox000Text);
			GuiLabel(layoutRecs[5], nameLabelText);
			GuiLabel(layoutRecs[6], classLabelText);
			GuiLabel(layoutRecs[7], equipmentLabelText);
			GuiLabel(layoutRecs[8], pointsLabelText);
			GuiLine(layoutRecs[9], NULL);
			GuiLine(layoutRecs[10], NULL);

			if (GuiTextBox(layoutRecs[11], charName0Text, 128, charName0EditMode)) charName0EditMode = !charName0EditMode;
			classSelect0Active = GuiToggleGroup(layoutRecs[12], classSelectText, classSelect0Active);
			if (GuiButton(layoutRecs[13], team->Slot0.GetWeaponData()->name.c_str())) SetPlayer(0);
			if (GuiButton(layoutRecs[14], cpModText)) SetPlayer(0);
			GuiLine(layoutRecs[15], NULL);

			if (GuiTextBox(layoutRecs[16], charName1Text, 128, charName1EditMode)) charName1EditMode = !charName1EditMode;
			classSelect1Active = GuiToggleGroup(layoutRecs[17], classSelectText, classSelect1Active);
			if (GuiButton(layoutRecs[18], team->Slot1.GetWeaponData()->name.c_str())) SetPlayer(1);
			if (GuiButton(layoutRecs[19], cpModText)) SetPlayer(1);
			GuiLine(layoutRecs[20], NULL);

			if (GuiTextBox(layoutRecs[21], charName2Text, 128, charName2EditMode)) charName2EditMode = !charName2EditMode;
			classSelect2Active = GuiToggleGroup(layoutRecs[22], classSelectText, classSelect2Active);
			if (GuiButton(layoutRecs[23], team->Slot2.GetWeaponData()->name.c_str())) SetPlayer(2);
			if (GuiButton(layoutRecs[24], cpModText)) SetPlayer(2);
			GuiLine(layoutRecs[25], NULL);

			if (GuiTextBox(layoutRecs[26], charName3Text, 128, charName3EditMode)) charName3EditMode = !charName3EditMode;
			classSelect3Active = GuiToggleGroup(layoutRecs[27], classSelectText, classSelect3Active);
			if (GuiButton(layoutRecs[28], team->Slot3.GetWeaponData()->name.c_str())) SetPlayer(3);
			if (GuiButton(layoutRecs[29], cpModText)) SetPlayer(3);

			GuiPanel(layoutRecs[30], NULL);
			GuiPanel(layoutRecs[31], NULL);
			GuiPanel(layoutRecs[32], NULL);
			GuiLine(layoutRecs[33], NULL);
			GuiPanel(layoutRecs[34], NULL);
			GuiLabel(layoutRecs[36], hpLabelText);
			GuiLabel(layoutRecs[37], mpLabelText);
			GuiLabel(layoutRecs[38], intiLabelText);
			GuiLabel(layoutRecs[39], strLabelText);
			GuiLabel(layoutRecs[40], dexLabelText);
			GuiLabel(layoutRecs[41], conLabelText);
			GuiLabel(layoutRecs[42], mndLabelText);
			if (GuiButton(layoutRecs[43], addText)) AddSTR();
			if (GuiButton(layoutRecs[44], addText)) AddDEX();
			if (GuiButton(layoutRecs[45], addText)) AddMND();
			if (GuiButton(layoutRecs[46], addText)) AddCON();
			if (GuiButton(layoutRecs[47], subText)) SubSTR();
			if (GuiButton(layoutRecs[48], subText)) SubDEX();
			if (GuiButton(layoutRecs[49], subText)) SubCON();
			if (GuiButton(layoutRecs[50], subText)) SubMND();
			GuiLabel(layoutRecs[51], std::to_string(strlvlText).c_str());
			GuiLabel(layoutRecs[52], std::to_string(dexlvlText).c_str());
			GuiLabel(layoutRecs[53], std::to_string(conlvlText).c_str());
			GuiLabel(layoutRecs[54], std::to_string(mndlvlText).c_str());
			GuiLabel(layoutRecs[55], std::to_string(cpRemainingText).c_str());
			GuiLabel(layoutRecs[56], damageLabel);
			GuiLabel(layoutRecs[57], weaponLabel);
			GuiLabel(layoutRecs[58], std::to_string(charHPText).c_str());
			GuiLabel(layoutRecs[59], std::to_string(charMPText).c_str());
			GuiLabel(layoutRecs[60], std::to_string(charINITText).c_str());
			GuiLabel(layoutRecs[61], charWeaponText.c_str());
			GuiLabel(layoutRecs[62], std::to_string(charDamageText).c_str());
			if (GuiDropdownBox(layoutRecs[35], DropdownBox035Text.c_str(), &DropdownBox035Active, DropdownBox035EditMode)) DropdownBox035EditMode = !DropdownBox035EditMode;
			DrawTextureEx(weaponTexture, Vector2{ characterDisplayAnchor.x + 0, characterDisplayAnchor.y + 30 }, 0, 3, WHITE);
			DrawTextureEx(classTexture, Vector2{ characterDisplayAnchor.x + -120, characterDisplayAnchor.y + 0 }, 0, 4, WHITE);

			if (GuiButton(layoutRecs[63], "Finish Edits")) finishScreen = 1;

			GuiUnlock();
		}

		// Gameplay Screen Unload logic
		void UnloadCreateScreen()
		{
			team->Slot0.SetMax();
			team->Slot1.SetMax();
			team->Slot2.SetMax();
			team->Slot3.SetMax();

			v->SaveTeam();
			UnloadTexture(weaponTexture);
			UnloadTexture(classTexture);

			v = nullptr;
			team = nullptr;
			selectedSlot = nullptr;
			//dont atually know if the memory of the char pointers 
			//is cleanded up or not but got an error when trying to do so. 
			//so not putting it here
		}

		// Gameplay Screen should finish?
		int FinishCreateScreen()
		{
			return finishScreen;
		}

		//------------------------------------------------------------------------------------
		// Controls Functions Definitions (local)
		//------------------------------------------------------------------------------------
		void AddSTR()
		{
			if (selectedSlot->GetCPtoSpend() > 0)
			{
				++selectedSlot->statistics.Str;
			}
		}
		void AddDEX()
		{
			if (selectedSlot->GetCPtoSpend() > 0)
			{
				++selectedSlot->statistics.Dex;
			}
		}
		void AddCON()
		{
			if (selectedSlot->GetCPtoSpend() > 0)
			{
				++selectedSlot->statistics.Con;
			}
		}
		void AddMND()
		{
			if (selectedSlot->GetCPtoSpend() > 0)
			{
				++selectedSlot->statistics.Mnd;
			}
		}
		void SubSTR()
		{
			if (selectedSlot->statistics.Str > 0)
			{
				--selectedSlot->statistics.Str;
			}
		}
		void SubDEX()
		{
			if (selectedSlot->statistics.Dex > 0)
			{
				--selectedSlot->statistics.Dex;
			}
		}
		void SubCON()
		{
			if (selectedSlot->statistics.Con > 0)
			{
				--selectedSlot->statistics.Con;
			}
		}
		void SubMND()
		{
			if (selectedSlot->statistics.Mnd > 0)
			{
				--selectedSlot->statistics.Mnd;
			}
		}

		void SetPlayer(const int i)
		{
			selectedSlot = team->GetPlayer(i);
			DropdownBox035Active = selectedSlot->weaponID;
			SetWeaponImage();
			SetClassImage();
		}

		void SetClass()
		{
			if (ShouldUpdateClass())
			{
				team->Slot0.SetClassID(classSelect0Active);
				team->Slot1.SetClassID(classSelect1Active);
				team->Slot2.SetClassID(classSelect2Active);
				team->Slot3.SetClassID(classSelect3Active);
				SetClassImage();
			}
			if (!(DropdownBox035Active == selectedSlot->weaponID))
			{
				selectedSlot->SetWeaponID(DropdownBox035Active);
				SetWeaponImage();
			}
		}

		void SetClassImage()
		{
			std::string temp = "resources/Art/";
			temp += selectedSlot->GetClassData()->name;
			temp += ".png";

			classTexture = UI::LoadTextureFromResources(temp.c_str());
		}

		void SetWeaponImage()
		{
			std::string temp = "resources/Art/";
			temp += selectedSlot->GetWeaponData()->name;
			temp += ".png";
			weaponTexture = UI::LoadTextureFromResources(temp.c_str());
		}


		void SetCharName()
		{
			team->Slot0.name = charName0Text;
			team->Slot1.name = charName1Text;
			team->Slot2.name = charName2Text;
			team->Slot3.name = charName3Text;
		}
		void UpdateStatBlock()
		{
			selectedSlot->SetMax();
			charHPText = selectedSlot->hp;
			charMPText = selectedSlot->mp;
			charINITText = selectedSlot->GetInitiative();
			charWeaponText = selectedSlot->GetWeaponData()->damage.GetString();
			charDamageText = selectedSlot->GetWeaponMod();
		}
		void UpdateStatModBlock()
		{
			cpRemainingText = selectedSlot->GetCPtoSpend();
			strlvlText = selectedSlot->statistics.Str;
			dexlvlText = selectedSlot->statistics.Dex;
			conlvlText = selectedSlot->statistics.Con;
			mndlvlText = selectedSlot->statistics.Mnd;
		}
		bool ShouldUpdateClass()
		{
			return (!(team->Slot0.classID == classSelect0Active &
				team->Slot1.classID == classSelect1Active &
				team->Slot2.classID == classSelect2Active &
				team->Slot3.classID == classSelect3Active));
		}
	}
}