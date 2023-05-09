#pragma once
#include <queue>
#include "PlayerTeam.h"
#include "AIController.h"

struct CompareInitiative {
	bool operator()(const Characters::Character* c1, const Characters::Character* c2) const
	{
		return c1->GetInitiative() > c2->GetInitiative();
	}
};

class InitiativeController
{
public:
	InitiativeController(Team::PlayerTeam* playerTeam, Team::AIController* aiTeam);
	~InitiativeController();

	Characters::Character* GetCharacactersTurn(bool& playerTurn);
	void DrawInitiativeDisplay(const Vector2& pos);

	void DrawIntDisplayBlock(float x, float y, Characters::Character* character) const;

private:
	std::deque<Characters::Character*>initiativeQueue;
};
