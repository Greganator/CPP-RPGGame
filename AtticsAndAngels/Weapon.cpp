#include "Weapon.h"
namespace Weapons
{
	Weapon::Weapon()
		:Weapon("Empty",WeaponType::None,Damage(0,DamageScale::d0),0)
	{
	}
	Weapon::Weapon(std::string name, WeaponType weapontype, Damage damage, int cooldown)
		:name(name), weapontype(weapontype), damage(damage)
	{}
	Weapon::Weapon(char* name, WeaponType weapontype, Damage damage, int cooldown)
		: name(name), weapontype(weapontype), damage(damage)
	{}
	int Weapon::PreformAttack(const int mod) const
	{
		int roll = 0;

		switch (damage.Die)
		{
		case DamageScale::d0:
			roll = 0;
			break;
		case DamageScale::d4:
			roll = GetRandomValue(1,4);
			break;
		case DamageScale::d6:
			roll = GetRandomValue(1, 6);
			break;
		case DamageScale::d8:
			roll = GetRandomValue(1, 8);
			break;
		case DamageScale::d10:
			roll = GetRandomValue(1, 10);
			break;
		case DamageScale::d12:
			roll = GetRandomValue(1, 12);
			break;
		}

		return roll+mod;
	}
}