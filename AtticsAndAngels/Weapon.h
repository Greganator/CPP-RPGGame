#pragma once
#include <string>
#include "Damage.h"
#include "raylib.h"
#include "thirdparty/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Weapons
{
	enum class WeaponType
	{
		None,
		Melee,
		Ranged,
		Magic
	};
	class Weapon
	{
	public:
		int ID = 0;
		std::string name;
		WeaponType weapontype;
		Damage damage;
		//smomething const effect;

	public:
		Weapon();
		Weapon(std::string name, WeaponType weapontype, Damage damage, int cooldown);
		Weapon(char* name, WeaponType weapontype, Damage damage, int cooldown);
		virtual ~Weapon() = default;
		Weapon(const Weapon& other) = default;
		Weapon& operator=(const Weapon& other) = default;
		Weapon(Weapon&& other) noexcept = default;
		Weapon& operator=(Weapon&& other) noexcept = default;

		int PreformAttack(const int mod) const;
	};

	inline void to_json(json& j, const Weapon& w)
	{
		j = json{{"ID",w.ID},{"name", w.name}, {"weapontype",w.weapontype}, {"damage", w.damage}};
	}
	inline void from_json(const json& j, Weapon& w)
	{
		j.at("ID").get_to(w.ID);
		j.at("name").get_to(w.name);
		j.at("weapontype").get_to(w.weapontype);
		j.at("damage").get_to(w.damage);
	}
}
