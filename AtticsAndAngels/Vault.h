#pragma once
#include "Character.h"
#include "AIEnimy.h"
#include "PlayerTeam.h"
#include <memory>
#include "thirdparty/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Vault
{
	/// <summary>
	/// Content vault for all Usable items abilities and weapons that exist in JSON
	/// </summary>
	class Vault
	{
	private:
		static inline std::unique_ptr<Vault> instance;

		std::map<const int, std::shared_ptr<Characters::Class>>  mClasses;
		std::map<const int, std::shared_ptr<Weapons::Weapon>> mWeapons;
		std::map<const int, std::shared_ptr<Characters::AIEnimy>>  mEnimies;

		std::shared_ptr<Team::PlayerTeam> mTeam;

		Vault();

	public:
		static Vault* const GetVault();

		Weapons::Weapon* GetWeapon(const int id) const noexcept;
		Characters::AIEnimy* GetEnimies(const int id) const noexcept;
		Characters::Class* GetClass(const int id) const noexcept;
		void ClearTeam();
		Team::PlayerTeam* GetTeam() const;
		void SaveTeam();
		void LoadTeamSave();
		Team::PlayerTeam* CreateTeam();
		std::vector<const char*> GetWeaponList();
		Characters::AIEnimy* GetRandomEnimy();

	private:
		template<typename T>
		T* GetItemPointerFromVault(const std::map<const int, std::shared_ptr<T>>& map, const int id) const noexcept;

		template<typename T>
		void PopulateMap(std::map <const int, std::shared_ptr<T>>& map);
	};
}
