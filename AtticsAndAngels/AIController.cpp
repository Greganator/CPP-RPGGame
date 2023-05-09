#include "AIController.h"
#include "Vault.h"

namespace Team
{
	AIController::AIController()
	{
		SetRandomSeed(time(0));

		Slot0 = GenerateSlot();
		Slot1 = GenerateSlot();
		Slot2 = GenerateSlot();
		Slot3 = GenerateSlot();

		Slot0.SetMax();
		Slot1.SetMax();
		Slot2.SetMax();
		Slot3.SetMax();
	}

	void AIController::TakeTurn(bool& isTakeingTurn, Characters::AIEnimy* character)
	{
		if (character->IsDead())
		{
			isTakeingTurn = false;
			return;
		}
		
		std::thread t(&AIController::DoTurn, this, std::ref(isTakeingTurn), character);
		t.detach();
	}

	Characters::AIEnimy* AIController::GetSlot(const int slot)
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
	bool AIController::AreAllCharacterDead()
	{
		return (Slot0.IsDead() && Slot1.IsDead() && Slot2.IsDead() && Slot3.IsDead());
	}
	Characters::AIEnimy AIController::GenerateSlot()
	{
		auto character = Vault::Vault::GetVault()->GetRandomEnimy();

		return Characters::AIEnimy(*character);
	}
	 void AIController::DoTurn(bool& isTakeingTurn, Characters::AIEnimy* character)
	{
		 long endTime = time(0)+3;

		 //add some time to make it look like the ai is thinking
		 while (time(0) < endTime) {}

		 PlayerTeam *playerTeam = Vault::Vault::GetVault()->GetTeam();

		 if (Characters::Character* c = playerTeam->HasBlocker(); c != nullptr)
		 {
			 character->Attack(c);
		 }
		 else
		 {
			 if (AttackTarget(character,playerTeam->GetPlayer(0)))
			 {

			 }
			 else if(AttackTarget(character, playerTeam->GetPlayer(1)))
			 {

			 }
			 else if (AttackTarget(character, playerTeam->GetPlayer(2)))
			 {

			 }
			 else if (AttackTarget(character, playerTeam->GetPlayer(3)))
			 {

			 }
		 }
	 
		 //add time to allow effects to play out
		 endTime = time(0) + 4;
		 while (time(0) < endTime) {}

		 isTakeingTurn = false;
		 return;
	}
	 bool AIController::AttackTarget(const Characters::AIEnimy* attacker,Characters::Character* target) const
	 {
		 if (target->IsDead())
		 {
			 return false;
		 }

		 attacker->Attack(target);

		 return true;
	 }
}