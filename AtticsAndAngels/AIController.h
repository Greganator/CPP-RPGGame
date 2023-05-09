#pragma once
#include "AIEnimy.h"

namespace Team
{
	class AIController
	{
	public:
		AIController();

		//set bool to false when turn is over
		void TakeTurn(bool& isTakeingTurn, Characters::AIEnimy* character);

		Characters::AIEnimy* GetSlot(const int slot);
		bool AreAllCharacterDead();

	private:
		Characters::AIEnimy Slot0;
		Characters::AIEnimy Slot1;
		Characters::AIEnimy Slot2;
		Characters::AIEnimy Slot3;

		Characters::AIEnimy GenerateSlot();
		void DoTurn(bool& isTakeingTurn, Characters::AIEnimy* character);
		bool AttackTarget(const Characters::AIEnimy* attacker,Characters::Character* target) const;
	};
}
