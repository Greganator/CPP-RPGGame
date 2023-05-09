#include "PlayerTeam.h"

namespace Team
{
	PlayerTeam::PlayerTeam()
	{
		Slot0 = Characters::Player();
		Slot1 = Characters::Player();
		Slot2 = Characters::Player();
		Slot3 = Characters::Player();
	}
	Characters::Player* PlayerTeam::GetPlayer(const int slot)
	{
		switch (slot)
		{
		case 0: 
			return &Slot0;
		case 1:
			return &Slot1;
		case 2:
			return &Slot2;
		case 3:
			return &Slot3;
		default:
			return &Slot0;
			break;
		}
	}
	Characters::Character* PlayerTeam::HasBlocker()
	{
		
		if (Slot0.isBlocking && !Slot0.IsDead())
		{
			return &Slot0;
		}
		if (Slot1.isBlocking && !Slot0.IsDead())
		{
			return &Slot1;
		}
		if (Slot2.isBlocking && !Slot0.IsDead())
		{
			return &Slot2;
		}
		if (Slot3.isBlocking && !Slot0.IsDead())
		{
			return &Slot3;
		}

		return nullptr;
	}
	bool PlayerTeam::AreAllCharacterDead()
	{
		return (Slot0.IsDead() && Slot1.IsDead() && Slot2.IsDead() && Slot3.IsDead());
	}
	void PlayerTeam::LevelUpTeam()
	{
		++Slot0.level;
		++Slot1.level;
		++Slot2.level;
		++Slot3.level;
	}
}