#include "Character.h"
#include <math.h>
#include "Vault.h"
#include"Screens/UIHelpers.h"

namespace Characters
{
	Character::Character()
		:Character("",0,0,0,0,0,1,0,0,0,0)
	{
	}
	void Character::Copy(const Character& other)
	{
		name = other.name;
		classID = other.classID;
		weaponID = other.weaponID;
		hp = other.hp;
		mp = other.mp;
		xp = other.xp;
		level = other.level;
		statistics = other.statistics;
		mClass = other.mClass;
		mWeapon = other.mWeapon;
	}
	void Character::Move(Character&& other)
	{
		name = other.name;
		classID = other.classID;
		weaponID = other.weaponID;
		hp = other.hp;
		mp = other.mp;
		xp = other.xp;
		level = other.level;
		statistics = other.statistics;
		mClass = other.mClass;
		mWeapon = other.mWeapon;

		other.name = "";
		other.classID = 0;
		other.weaponID = 0;
		other.hp = 0;
		other.mp = 0;
		other.xp = 0;
		other.level = 0;
		other.statistics = Stats();
		other.mClass = nullptr;
		other.mWeapon = nullptr;
	}
	Character::Character(std::string cName, int cClassID, int cWeaponID, int cHP, int cMP, int cXP, int cLevel, int s, int d, int c, int m)
		:Character(cName, cClassID, cWeaponID, cHP, cMP, cXP, cLevel, Stats(s,d,c,m))
	{
	}
	Character::Character(std::string cName, int cClassID, int cWeaponID, int cHP, int cMP, int cXP, int cLevel, Stats cStats)
		:name(cName), classID(cClassID), weaponID(cWeaponID), hp(cHP), mp(cMP), xp(cXP), 
		level(cLevel), statistics(cStats), mClass(nullptr), mWeapon(nullptr)
	{
	}
	Character::~Character()
	{
		mWeapon = nullptr;
		mClass = nullptr;
		delete animator;
		animator = nullptr;
	}
	Character::Character(const Character& other)
	{
		Copy(other);
	}
	Character& Character::operator=(const Character& other)
	{
		if (this != &other)
		{
			Copy(other);
		}

		return *this;
	}
	Character::Character(Character&& other) noexcept
	{
		Move(std::move(other));
	}
	Character& Character::operator=(Character&& other) noexcept
	{
		if (this != &other)
		{
			Move(std::move(other));
		}

		return *this;
	}
	void Character::EnableAnimator()
	{
		if (animator != nullptr)
		{
			delete animator;
			animator = nullptr;
		}

		animator = new CharacterAnimator(GetClassData()->name, false);
	}
	void Character::UpdateCharacter(const Vector2& position)
	{
		if (animator != nullptr)
		{
			float hpPercent = 0;
			if (MAXHP != 0)
			{
				hpPercent = float(hp) / float(MAXHP);
			}
			float mpPercent = 0;
			if (MAXMP != 0)
			{
				mpPercent = float(mp) / float(MAXMP);
			}

			if (IsDead() != mPreviousDeathState)
			{
				mPreviousDeathState = IsDead();

				if (IsDead())
				{
					animator->SetState(CharacterState::DIE);
					LoadRandomAudioOneShot(CharacterState::DIE);
				}
				else
				{
					animator->SetState(CharacterState::IDLE);
				}
			}
			if (!IsDead())
			{
				Screens::UI::DrawValueBar(position.x, position.y + 10, 120, hpPercent, RED);
				Screens::UI::DrawValueBar(position.x, position.y + 20, 120, mpPercent, BLUE);
			}

			animator->AnimateCharacater(position);
	
		}
	}
	void Character::Attack(Character* target) const
	{
		animator->SetState(CharacterState::ATTACK);
		int mod = GetWeaponMod();
		int damage = GetWeaponData()->PreformAttack(mod);
		LoadRandomAudioOneShot(CharacterState::ATTACK);

		target->TakeAttack(mod, damage);

	}
	void Character::Heal( Character* target)
	{
		animator->SetState(CharacterState::HEAL);
		LoadRandomAudioOneShot(CharacterState::HEAL);

		target->hp += GetTotalStats().Mnd * 2;
	}
	void Character::Block()
	{
		animator->SetState(CharacterState::BLOCK);
		isBlocking = true;
		LoadRandomAudioOneShot(CharacterState::BLOCK);
	}
	void Character::CastSpell(Character* target)
	{
		animator->SetState(CharacterState::SPELL);
		LoadRandomAudioOneShot(CharacterState::SPELL);

		if (mp > 0)
		{
			mp -= 2*level;

			target->TakeAttack(mp * level, GetTotalStats().Mnd);
		}
	}
	void Character::SetIdle()
	{
		isBlocking = false;
		animator->SetState(CharacterState::IDLE);
	}
	void Character::TakeAttack(const int mod, const int damage)
	{
		animator->SetState(CharacterState::HIT);

		Stats ts = GetTotalStats();

		float dodge = (float(ts.Dex) / float(mod))*95;
		if (float rand = GetRandomValue(1, 100); rand > dodge)
		{
			hp -= (damage -(damage * (ts.Con / 100)));
		}

		LoadRandomAudioOneShot(CharacterState::HIT);
	}
	const int Character::GetInitiative() const
	{
		Stats stats = GetTotalStats();

		initiative = stats.Dex + floor(stats.Mnd / 2);

		return initiative;
	}

	void Character::SetClassID(const int id)
	{
		classID = id;
		mClass = Vault::Vault::GetVault()->GetClass(id);
	}

	void Character::SetWeaponID(const int id)
	{
		weaponID = id;
		mWeapon = Vault::Vault::GetVault()->GetWeapon(id);
	}

	const Stats& Character::GetTotalStats() const
	{
		Stats stats = statistics;
		stats =  stats + (GetClassData()->classBonus * level);

		return stats;
	}
	void Character::SetMax()
	{
		auto stats = GetTotalStats();

		GetInitiative();
		hp = (stats.Str + stats.Con * 2) * level;
		MAXHP = hp;
		mp = (stats.Mnd * 2) * level;
		MAXMP = mp;
	}
	const int Character::GetWeaponMod() const
	{
		switch (GetWeaponData()->weapontype)
		{
		case Weapons::WeaponType::Magic:
			return  mWeapon->damage.Mod + (GetTotalStats().Mnd * 1.8);
				break;
		case Weapons::WeaponType::Melee:
			return  mWeapon->damage.Mod + (GetTotalStats().Str * 1.5);
			break;
		case Weapons::WeaponType::Ranged:
			return  mWeapon->damage.Mod + (GetTotalStats().Dex * 1.2);
			break;
		}
	}
	void Character::DrawCharacterDefault(const Vector2& position) const
	{
		return animator->DrawDefaultState(position);
	}
	void Character::DrawCharacterDead(const Vector2& position) const
	{
		return animator->DrawDeadState(position);
	}
	bool Character::IsDead() const
	{
		return hp <= 0;
	}

#pragma optimize("", off)
	Weapons::Weapon* Character::GetWeaponData() const
	{
		if (!mWeapon)
		{
			mWeapon = Vault::Vault::GetVault()->GetWeapon(weaponID);
		}
		return mWeapon;
	}

	Class* Character::GetClassData() const
	{
		if (!mClass)
		{
			mClass = Vault::Vault::GetVault()->GetClass(classID);
		}
		return mClass;
	}
}