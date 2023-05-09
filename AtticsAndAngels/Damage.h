#pragma once
#include "thirdparty/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Weapons
{
	enum class DamageScale
	{
		d0,
		d4,
		d6,
		d8,
		d10,
		d12
	};
	struct Damage
	{
		int Mod;
		DamageScale Die;
		Damage(int mod, DamageScale die);
		const char* GetString();
	};
	inline void to_json(json& j, const Damage& d)
	{
		j = json{ {"Mod", d.Mod}, {"Die", d.Die}};
	}
	inline void from_json(const json& j, Damage& d)
	{
		j.at("Mod").get_to(d.Mod);
		j.at("Die").get_to(d.Die);
	}
}
