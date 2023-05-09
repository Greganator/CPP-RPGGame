#include "Magic.h"
namespace Weapons
{
	Weapons::Magic::Magic(std::string name, Damage damage, int cooldown)
		:Weapon(name, WeaponType::Magic, damage, cooldown)
	{
	}
}
