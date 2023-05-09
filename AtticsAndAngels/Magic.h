#pragma once
#include "Weapon.h"

namespace Weapons
{
	class Magic : public Weapon
	{
	public:
		Magic(std::string name, Damage damage, int cooldown);
	};

	inline void to_json(json& j, const Magic& w)
	{
		j = json{ {"ID",w.ID},{"name", w.name}, {"weapontype",w.weapontype}, {"damage", w.damage} };
	}
	inline void from_json(const json& j, Magic& w)
	{
		j.at("ID").get_to(w.ID);
		j.at("name").get_to(w.name);
		j.at("weapontype").get_to(w.weapontype);
		j.at("damage").get_to(w.damage);
	}
}
