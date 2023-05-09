#include "Damage.h"

namespace Weapons
{
	Damage::Damage(int mod, DamageScale die)
		:Mod(mod), Die(die)
	{
	}
	const char* Damage::GetString()
	{
		switch (Die)
		{
		case DamageScale::d4:
			return "d4";
			break;
		case DamageScale::d6:
			return "d6";
			break;
		case DamageScale::d8:
			return "d8";
			break;
		case DamageScale::d10:
			return "d10";
			break;
		case DamageScale::d12:
			return "d12";
			break;

		default:
			return "d0";
			break;
		}
	}
}