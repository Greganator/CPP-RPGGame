#include "Ranged.h"
namespace Weapons
{
	Ranged::Ranged(std::string name, Damage damage, int cooldown)
		:Weapon(name, WeaponType::Ranged, damage, cooldown)
	{
	}
}
