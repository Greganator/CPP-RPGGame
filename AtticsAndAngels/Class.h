#pragma once
#include <string>
#include "thirdparty/nlohmann/json.hpp"
#include "Stats.h"
using json = nlohmann::json;

namespace Characters
{
	struct Class
	{
		int ID;
		std::string name;
		Stats classBonus;
		//Spells
		//Abillities TODO add spells and abilities if I have time
	};

	inline void to_json(json& j, const Class& c)
	{
		j = json{ {"ID",c.ID}, {"name", c.name}, {"classBonus",c.classBonus}};
	}
	inline void from_json(const json& j, Class& c)
	{
		j.at("ID").get_to(c.ID);
		j.at("name").get_to(c.name);
		j.at("classBonus").get_to(c.classBonus);
	}
}
