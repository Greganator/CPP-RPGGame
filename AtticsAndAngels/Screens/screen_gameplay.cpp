#include "screens.h"
#include "../AIController.h"
#include "../InitiativeController.h"

namespace Screens
{
	//----------------------------------------------------------------------------------
	// Module Variables Definition (local)
	//----------------------------------------------------------------------------------
	static int framesCounter = 0;
	static int finishScreen = 0;

	namespace Scenes::Gameplay
	{
		enum class ActiveButton
		{
			None,
			Attack,
			Heal,
			Block,
			Spell
		};

		//Character SpawnPositions
		Vector2 BattlefeildTopPlayer;
		Vector2 BattlefeildTopEnimies;

		Vector2 Slot00Pos;
		Vector2 Slot01Pos;
		Vector2 Slot02Pos;
		Vector2 Slot03Pos;

		Vector2 EnemySlot00Pos;
		Vector2 EnemySlot01Pos;
		Vector2 EnemySlot02Pos;
		Vector2 EnemySlot03Pos;

		Vector2 actionGroupAnchor;

		ActiveButton activeButton;

		InitiativeController* intController;

		void Button00Target();
		void Button01Target();
		void Button02Target();
		void Button03Target();

		void ButtonAttackActive(bool b);
		void ButtonHealActive(bool b);
		void ButtonBlockActive(bool b);
		void ButtonSpellActive(bool b);

		void PerformAction(const int target);
		void TargetOpponent(const int target);
		void TargetTeam(const int target);

		Texture2D SetClassImage(Characters::Player& chr);

		bool isButtonAttackActive = false;
		bool isButtonHealActive = false;
		bool isButtonBlockActive = false;
		bool isButtonSpellActive = false;

		bool isTakeingTurn = false;
		bool isPlayerTurn = false;

		Vault::Vault* v;
		Team::PlayerTeam* team;
		Team::AIController* aiTeam;
		Characters::Character* selectedSlot;

		//Textures
		Texture2D backgroundTop;
		Texture2D backgroundBottom;

		// Gameplay Screen Initialization logic
		void InitGameplayScreen()
		{
			isTakeingTurn = false;
			framesCounter = 0;
			finishScreen = 0;

			isButtonAttackActive = false;
			isButtonHealActive = false;
			isButtonBlockActive = false;
			isButtonSpellActive = false;

			activeButton = ActiveButton::None;

			BattlefeildTopPlayer = UI::GetSceenPosFromPrecentage(.4, .4);
			BattlefeildTopEnimies = UI::GetSceenPosFromPrecentage(.6, .4);

			Slot00Pos = { BattlefeildTopPlayer.x - 120, BattlefeildTopPlayer.y + 48 };
			Slot01Pos = { BattlefeildTopPlayer.x - 144, BattlefeildTopPlayer.y + 120 };
			Slot02Pos = { BattlefeildTopPlayer.x - 168, BattlefeildTopPlayer.y + 192 };
			Slot03Pos = { BattlefeildTopPlayer.x - 192, BattlefeildTopPlayer.y + 264 };

			EnemySlot00Pos = { BattlefeildTopEnimies.x + 120, BattlefeildTopEnimies.y + 48 };
			EnemySlot01Pos = { BattlefeildTopEnimies.x + 144, BattlefeildTopEnimies.y + 120 };
			EnemySlot02Pos = { BattlefeildTopEnimies.x + 168, BattlefeildTopEnimies.y + 192 };
			EnemySlot03Pos = { BattlefeildTopEnimies.x + 192, BattlefeildTopEnimies.y + 264 };

			actionGroupAnchor = UI::GetSceenPosFromPrecentage(.5, .95);

			v = Vault::Vault::GetVault();
			team = v->GetTeam();
			selectedSlot = team->GetPlayer(0);
			aiTeam = new Team::AIController();

			//Replace this with random Backround graber
			backgroundTop = UI::LoadRandomTopBackground();
			backgroundBottom = UI::LoadRandomBottomBackground();

			UI::LoadRandomBackgroundmusic("resources/Audio/BattleScreen/", music);

			aiTeam->GetSlot(0)->EnableAnimator();
			aiTeam->GetSlot(1)->EnableAnimator();
			aiTeam->GetSlot(2)->EnableAnimator();
			aiTeam->GetSlot(3)->EnableAnimator();

			team->Slot0.EnableAnimator();
			team->Slot1.EnableAnimator();
			team->Slot2.EnableAnimator();
			team->Slot3.EnableAnimator();

			intController = new InitiativeController(team, aiTeam);
		}

		Texture2D SetClassImage(Characters::Player& chr)
		{
			std::string temp = "resources/Art/";
			temp += chr.GetClassData()->name;
			temp += ".png";

			return UI::LoadTextureFromResources(temp.c_str());
		}

		// Gameplay Screen Update logic
		void UpdateGameplayScreen()
		{
			if (!isTakeingTurn)
			{
				isTakeingTurn = true;

				selectedSlot = intController->GetCharacactersTurn(isPlayerTurn);

				if (selectedSlot->IsDead())
				{
					isTakeingTurn = false;
					return;
				}

				selectedSlot->SetIdle();

				if (isPlayerTurn)
				{
					return;
				}

				aiTeam->TakeTurn(isTakeingTurn, (Characters::AIEnimy*)selectedSlot);
			}

			if (team->AreAllCharacterDead() || aiTeam->AreAllCharacterDead())
			{
				isTakeingTurn = true;
				finishScreen = 1;
			}
		}

		// Gameplay Screen Draw logic
		void DrawGameplayScreen()
		{
			//Draw background
			UI::DrawBackgroundTexture(backgroundBottom, WHITE);
			UI::DrawBackgroundTexture(backgroundTop, WHITE);

			//Draw Initiative
			intController->DrawInitiativeDisplay(UI::GetSceenPosFromPrecentage(.375f, 0));
			Vector2 pos = UI::GetSceenPosFromPrecentage(.5f, 0);
			intController->DrawIntDisplayBlock(pos.x, pos.y + 70, selectedSlot);

			//DrawCharacters
			team->Slot0.UpdateCharacter(Slot00Pos);
			team->Slot1.UpdateCharacter(Slot01Pos);
			team->Slot2.UpdateCharacter(Slot02Pos);
			team->Slot3.UpdateCharacter(Slot03Pos);

			aiTeam->GetSlot(0)->UpdateCharacter(EnemySlot00Pos);
			aiTeam->GetSlot(1)->UpdateCharacter(EnemySlot01Pos);
			aiTeam->GetSlot(2)->UpdateCharacter(EnemySlot02Pos);
			aiTeam->GetSlot(3)->UpdateCharacter(EnemySlot03Pos);

			//DrawControls
			if (isPlayerTurn)
			{
				GuiGroupBox(Rectangle{ actionGroupAnchor.x + -312, actionGroupAnchor.y + -264, 624, 264 }, NULL);
				ButtonAttackActive(GuiToggle(Rectangle{ actionGroupAnchor.x + -288, actionGroupAnchor.y + -264, 120, 48 }, "Attack", isButtonAttackActive));
				ButtonHealActive(GuiToggle(Rectangle{ actionGroupAnchor.x + -288, actionGroupAnchor.y + -192, 120, 48 }, "Heal", isButtonHealActive));
				ButtonBlockActive(GuiToggle(Rectangle{ actionGroupAnchor.x + -288, actionGroupAnchor.y + -120, 120, 48 }, "Block", isButtonBlockActive));
				ButtonSpellActive(GuiToggle(Rectangle{ actionGroupAnchor.x + -288, actionGroupAnchor.y + -48, 120, 48 }, "Spell", isButtonSpellActive));

				switch (activeButton)
				{
				case ActiveButton::Attack:
					if (!aiTeam->GetSlot(0)->IsDead())if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -264, 120, 48 }, aiTeam->GetSlot(0)->name.c_str())) Button00Target();
					if (!aiTeam->GetSlot(1)->IsDead())if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -192, 120, 48 }, aiTeam->GetSlot(1)->name.c_str())) Button01Target();
					if (!aiTeam->GetSlot(2)->IsDead())if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -120, 120, 48 }, aiTeam->GetSlot(2)->name.c_str())) Button02Target();
					if (!aiTeam->GetSlot(3)->IsDead())if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -48, 120, 48 }, aiTeam->GetSlot(3)->name.c_str())) Button03Target();
					break;
				case ActiveButton::Heal:
					if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -264, 120, 48 }, team->Slot0.name.c_str())) Button00Target();
					if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -192, 120, 48 }, team->Slot1.name.c_str())) Button01Target();
					if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -120, 120, 48 }, team->Slot2.name.c_str())) Button02Target();
					if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -48, 120, 48 }, team->Slot3.name.c_str())) Button03Target();
					break;
				case ActiveButton::Block:
					if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -264, 120, 264 }, "BLOCK")) Button00Target();
					break;
				case ActiveButton::Spell:
					if (!aiTeam->GetSlot(0)->IsDead())if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -264, 120, 48 }, aiTeam->GetSlot(0)->name.c_str())) Button00Target();
					if (!aiTeam->GetSlot(1)->IsDead())if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -192, 120, 48 }, aiTeam->GetSlot(1)->name.c_str())) Button01Target();
					if (!aiTeam->GetSlot(2)->IsDead())if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -120, 120, 48 }, aiTeam->GetSlot(2)->name.c_str())) Button02Target();
					if (!aiTeam->GetSlot(3)->IsDead())if (GuiButton(Rectangle{ actionGroupAnchor.x + 0, actionGroupAnchor.y + -48, 120, 48 }, aiTeam->GetSlot(3)->name.c_str())) Button03Target();
					break;
				}
			}
			//Draw Effects
		}

		// Gameplay Screen Unload logic
		void UnloadGameplayScreen()
		{
			isTakeingTurn = false;
			v = nullptr;
			team = nullptr;
			selectedSlot = nullptr;
			delete aiTeam;
			aiTeam = nullptr;
			delete intController;
			intController = nullptr;

		}

		// Gameplay Screen should finish?
		int FinishGameplayScreen()
		{
			return finishScreen;
		}
		void Button00Target()
		{
			PerformAction(0);
		}
		void Button01Target()
		{
			PerformAction(1);
		}
		void Button02Target()
		{
			PerformAction(2);
		}
		void Button03Target()
		{
			PerformAction(3);
		}
		void ButtonAttackActive(bool b)
		{
			if (b)
			{
				GuiLine(Rectangle{ actionGroupAnchor.x + -168, actionGroupAnchor.y + -264, 168, 32 }, NULL);
				if (activeButton != ActiveButton::Attack)
				{
					activeButton = ActiveButton::Attack;
					isButtonAttackActive = true;
					isButtonHealActive = false;
					isButtonBlockActive = false;
					isButtonSpellActive = false;
				}
			}
		}
		void ButtonHealActive(bool b)
		{
			if (b)
			{
				GuiLine(Rectangle{ actionGroupAnchor.x + -168, actionGroupAnchor.y + -192, 168, 32 }, NULL);
				if (activeButton != ActiveButton::Heal)
				{
					activeButton = ActiveButton::Heal;
					isButtonHealActive = true;
					isButtonAttackActive = false;
					isButtonBlockActive = false;
					isButtonSpellActive = false;
				}
			}
		}
		void ButtonBlockActive(bool b)
		{
			if (b)
			{
				GuiLine(Rectangle{ actionGroupAnchor.x + -168, actionGroupAnchor.y + -120, 168, 32 }, NULL);
				if (activeButton != ActiveButton::Block)
				{
					activeButton = ActiveButton::Block;
					isButtonBlockActive = true;
					isButtonAttackActive = false;
					isButtonHealActive = false;
					isButtonSpellActive = false;
				}
			}
		}
		void ButtonSpellActive(bool b)
		{
			if (b)
			{
				GuiLine(Rectangle{ actionGroupAnchor.x + -168, actionGroupAnchor.y + -48, 168, 32 }, NULL);
				if (activeButton != ActiveButton::Spell)
				{
					activeButton = ActiveButton::Spell;
					isButtonSpellActive = true;
					isButtonAttackActive = false;
					isButtonHealActive = false;
					isButtonBlockActive = false;
				}
			}
		}

		void PerformAction(const int target)
		{
			switch (activeButton)
			{
			case ActiveButton::Attack:
				TargetOpponent(target);
				break;
			case ActiveButton::Heal:
				TargetTeam(target);
				break;
			case ActiveButton::Block:
				selectedSlot->Block();
				break;
			case ActiveButton::Spell:
				TargetOpponent(target);
				break;
			}
			isTakeingTurn = false;
		}

		void TargetOpponent(const int target)
		{
			switch (activeButton)
			{
			case Screens::Scenes::Gameplay::ActiveButton::Attack:
				selectedSlot->Attack(aiTeam->GetSlot(target));
				break;
			case Screens::Scenes::Gameplay::ActiveButton::Spell:
				selectedSlot->CastSpell(aiTeam->GetSlot(target));
				break;
			}

		}
		void TargetTeam(const int target)
		{
			selectedSlot->Heal(team->GetPlayer(target));
		}
	}
}