#pragma once
#include "Character.h"

namespace Characters
{
	class Player : public Character
	{
	public:
		Player();
		Player(std::string cName, int cClassID, int cWeaponID, int cHP, int cMP, int cXP, int cLevel, int s, int d, int c, int m);
		Player(std::string cName, int cClassID, int cWeaponID, int cHP, int cMP, int cXP, int cLevel, Stats cStats);
		~Player() = default;
		Player(const Player& other);
		Player& operator=(const Player& other);
		Player(Player&& other) noexcept;
		Player& operator=(Player&& other) noexcept;

		int GetCPtoSpend() const;
	private:
		int const mCPtoSpendPerLvl = 10;
		int GetCPSpent() const;
	};

	inline void to_json(json& j, const Player& c)
	{
		j = json{ {"name",c.name},{"classID", c.classID},{"weaponID", c.weaponID},
			{"statistics", c.statistics},{"hp", c.hp},{"mp",c.mp},{"xp", c.xp},{"level", c.level} };
	}

	inline void from_json(const json& j, Player& c)
	{
		j.at("name").get_to(c.name);
		j.at("classID").get_to(c.classID);
		j.at("weaponID").get_to(c.weaponID);
		j.at("statistics").get_to(c.statistics);
		j.at("hp").get_to(c.hp);
		j.at("mp").get_to(c.mp);
		j.at("xp").get_to(c.xp);
		j.at("level").get_to(c.level);
	}
}