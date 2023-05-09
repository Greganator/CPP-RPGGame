#include "Melee.h"
namespace Weapons
{
	Melee::Melee(std::string name, Damage damage, int cooldown)
		:Weapon(name, WeaponType::Melee,damage,cooldown)
	{
	}
}
