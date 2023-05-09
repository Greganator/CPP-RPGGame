#pragma once
#include "Weapon.h"
#include "Class.h"
#include "Stats.h"
#include <memory>
#include "CharacterAnimator.h"
#include <thread>


namespace Characters
{
	class Character
	{
	public:
		std::string name;
		int classID;
		int weaponID;
		Stats statistics;
		int hp; //Health Points
		int mp; //Mind Points
		int xp; //experience points
		int level;
		bool isBlocking = false;

	protected:
		// should never be exposed to a user, is mutable just in case it is not initialized
		mutable Weapons::Weapon* mWeapon;
		mutable Class* mClass;
		//exists for debug reasons
		mutable int initiative = 0;
		bool mPreviousDeathState = false;


		CharacterAnimator* animator = nullptr;
		bool shouldAnimate = false;
		virtual void Copy(const Character& other); 
		virtual void Move(Character&& other);
		int MAXHP;
		int MAXMP;

	public:
		Character();
		Character(std::string cName, int cClassID, int cWeaponID, int cHP, int cMP, int cXP, int cLevel, int s, int d, int c, int m);
		Character(std::string cName, int cClassID, int cWeaponID, int cHP, int cMP, int cXP, int cLevel, Stats cStats);
		virtual ~Character();
		Character(const Character& other);
		Character& operator=(const Character& other);
		Character(Character&& other) noexcept;
		Character& operator=(Character&& other) noexcept;

		virtual void EnableAnimator();
		void UpdateCharacter(const Vector2& position);

		void Attack(Character* target) const;
		void Heal(Character* target);
		void Block();
		void CastSpell(Character* target);
		void SetIdle();

		void TakeAttack(const int mod, const int damage);

		const int GetInitiative() const;
		void SetClassID(const int id);
		void SetWeaponID(const int id);
		Weapons::Weapon* GetWeaponData() const;
		Class* GetClassData() const;
		const Stats& GetTotalStats() const;
		void SetMax();
		const int GetWeaponMod() const;

		void DrawCharacterDefault(const Vector2& position) const;
		void DrawCharacterDead(const Vector2& position) const;
		bool IsDead() const;
		static inline bool LOADAUDIO;

	private:
		inline void PlayAudioThread(CharacterState state) const
		{
			try
			{
				
				SetRandomSeed(time(0));
				std::string directory = "resources/Audio/" + GetClassData()->name + "/" + CharacterAnimator::GetEnumName(state) + "/";

				std::vector<const char*> filter = std::vector<const char*>();

				int filecount = 0;
				while (LOADAUDIO)
				{
					_sleep(.01);
				}
				LOADAUDIO = true;
				auto files = GetDirectoryFiles(directory.c_str(), &filecount);

				for (int i = 0; i < filecount; ++i)
				{
					if (!IsFileExtension(files[i], ".wav") && !IsFileExtension(files[i], ".ogg")) continue;

					filter.push_back(files[i]);
				}

				auto file = GetRandomValue(0, filter.size() - 1);
				LOADAUDIO = false;
				if (filter.size() > 0)
				{
					auto SFX = LoadSound((directory + filter[file]).c_str());
					filter.clear();
					PlaySound(SFX);
					long endTime = time(0) + 4;
					while (time(0) < endTime) {}
					UnloadSound(SFX);
				}
			}
			catch (...)
			{
				TraceLog(LOG_ERROR, "An Error occured in Play Audio thread, Most likly audio stomping each other");
			}
		}

		inline void LoadRandomAudioOneShot(CharacterState state) const
		{
			std::thread t(&Character::PlayAudioThread, this, state);
			t.detach();
		}
	};

	inline void to_json(json& j, const Character& c)
	{
		j = json{ {"name",c.name},{"classID", c.classID},{"weaponID", c.weaponID},
			{"statistics", c.statistics},{"hp", c.hp},{"mp",c.mp},{"xp", c.xp},{"level", c.level} };
	}

	inline void from_json(const json& j, Character& c)
	{
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
