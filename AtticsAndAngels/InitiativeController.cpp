#include "InitiativeController.h"
#include "Screens/UIHelpers.h"

InitiativeController::InitiativeController(Team::PlayerTeam* playerTeam, Team::AIController* aiTeam)
{
	initiativeQueue.push_back(&playerTeam->Slot0);
	initiativeQueue.push_back(&playerTeam->Slot1);
	initiativeQueue.push_back(&playerTeam->Slot2);
	initiativeQueue.push_back(&playerTeam->Slot3);
	initiativeQueue.push_back(aiTeam->GetSlot(0));
	initiativeQueue.push_back(aiTeam->GetSlot(1));
	initiativeQueue.push_back(aiTeam->GetSlot(2));
	initiativeQueue.push_back(aiTeam->GetSlot(3));

	std::stable_sort(initiativeQueue.begin(),initiativeQueue.end(), CompareInitiative());
}

InitiativeController::~InitiativeController()
{
}

//returns true if player charater false if AI
 Characters::Character* InitiativeController::GetCharacactersTurn(bool& playerTurn)
{
	auto characterTurn = initiativeQueue.front();
	initiativeQueue.pop_front();
	initiativeQueue.push_back(characterTurn);

	playerTurn = typeid(*characterTurn) == typeid(Characters::Player);

	return characterTurn;
}

void InitiativeController::DrawInitiativeDisplay(const Vector2& pos)
{
	int number = 0;
	for (auto i = initiativeQueue.begin(); i != initiativeQueue.end(); ++i)
	{
		Characters::Character* character = *i;
		DrawIntDisplayBlock(pos.x + (70 * number), pos.y, character);
		++number;
	}
}

void InitiativeController::DrawIntDisplayBlock(float x, float y, Characters::Character* character) const
{
	if (character != nullptr)
	{
		GuiPanel(Rectangle{ x, y,70,70 }, NULL);
		if (character->IsDead())
		{
			character->DrawCharacterDead(Vector2{ x, y });
		}
		else
		{
			character->DrawCharacterDefault(Vector2{ x, y });
		}
		GuiLabel(Rectangle{ x, y + 40,70,20 }, character->name.c_str());
	}
}
