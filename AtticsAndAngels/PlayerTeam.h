#pragma once
#include "Player.h"

namespace Team
{
	class PlayerTeam
	{
	public:
	 	static inline const std::string name = "PlayerSave";

		Characters::Player Slot0;
		Characters::Player Slot1;
		Characters::Player Slot2;
		Characters::Player Slot3;

		PlayerTeam();

		Characters::Player* GetPlayer(const int slot);
		Characters::Character* HasBlocker();
		bool AreAllCharacterDead();
		void LevelUpTeam();
	};

	inline void to_json(json& j, const PlayerTeam& c)
	{
		j = json{ {"Slot0",c.Slot0}, {"Slot1",c.Slot1},{"Slot2",c.Slot2} ,{"Slot3",c.Slot3} };
	}

	inline void from_json(const json& j, PlayerTeam& c)
	{
		j.at("Slot0").get_to(c.Slot0);
		j.at("Slot1").get_to(c.Slot1);
		j.at("Slot2").get_to(c.Slot2);
		j.at("Slot3").get_to(c.Slot3);
	}
}