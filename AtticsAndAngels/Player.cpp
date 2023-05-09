#include "Player.h"

namespace Characters
{
	int Player::GetCPtoSpend() const
	{
		return (mCPtoSpendPerLvl*level)-GetCPSpent();
	}
	int Player::GetCPSpent() const
	{
		return statistics.Con + statistics.Dex + statistics.Mnd + statistics.Str;
	}
	Player::Player()
		:Character()
	{
	}
	Player::Player(std::string cName, int cClassID, int cWeaponID, int cHP, int cMP, int cXP, int cLevel, int s, int d, int c, int m)
		: Character(cName, cClassID, cWeaponID, cHP, cMP, cXP, cLevel, s, d, c, m)
	{

	}
	Player::Player(std::string cName, int cClassID, int cWeaponID, int cHP, int cMP, int cXP, int cLevel, Stats cStats)
		:Character(cName, cClassID, cWeaponID, cHP, cMP, cXP, cLevel, cStats)
	{
	}
	Player::Player(const Player& other)
	{
		Copy(other);
	}
	Player& Player::operator=(const Player& other)
	{
		if (this != &other)
		{
			Copy(other);
		}

		return *this;
	}
	Player::Player(Player&& other) noexcept
	{
		Move(std::move(other));
	}
	Player& Player::operator=(Player&& other) noexcept
	{
		if (this != &other)
		{
			Move(std::move(other));
		}

		return *this;
	}
}