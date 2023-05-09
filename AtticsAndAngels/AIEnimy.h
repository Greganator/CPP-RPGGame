#pragma once
#include "Character.h"

namespace Characters
{
	class AIEnimy : public Character
	{
	public:
		int ID;

		void EnableAnimator() override;
	};

	inline void to_json(json& j, const AIEnimy& c)
	{
		j = json{ {"ID", c.ID} ,{"name",c.name},{"classID", c.classID},{"weaponID", c.weaponID},
			{"statistics", c.statistics},{"hp", c.hp},{"mp",c.mp},{"xp", c.xp},{"level", c.level} };
	}

	inline void from_json(const json& j, AIEnimy& c)
	{
		j.at("ID").get_to(c.ID);
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
