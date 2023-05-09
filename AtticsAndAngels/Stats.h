#pragma once
#include "thirdparty/nlohmann/json.hpp"
using json = nlohmann::json;

struct Stats
{
	//Melee weapon use and damage, Health
	int Str;
	//Ranged Weapon use and damage, Inititive, chance to dodge
	int Dex;
	//Health, Risistance to Damage,
	int Con;
	//Magic Weapon use and damage, Inititive, XP gain mod, Mind Points
	int Mnd;

	Stats();
	Stats(int s, int d, int c, int m);
	Stats operator+(const Stats other);
	Stats operator*(const int i);
};

inline void to_json(json& j, const Stats& s)
{
	j = json{ {"Str",s.Str},{"Dex", s.Dex},{"Con", s.Con},{"Mnd", s.Mnd} };
}

inline void from_json(const json& j, Stats& s)
{
	j.at("Str").get_to(s.Str);
	j.at("Dex").get_to(s.Dex);
	j.at("Con").get_to(s.Con);
	j.at("Mnd").get_to(s.Mnd);
}
