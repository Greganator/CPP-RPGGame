#include "Vault.h"
#include "JsonSaveLoad.h"

namespace Vault
{
	Vault::Vault()
	{
		PopulateMap(mClasses);
		PopulateMap(mWeapons);
		PopulateMap(mEnimies);
	}

	Vault* const Vault::GetVault()
	{
		if (!instance)
		{
			instance = std::make_unique<Vault>(Vault());
		}

		return instance.get();
	}
	Weapons::Weapon* Vault::GetWeapon(const int id) const noexcept
	{
		return GetItemPointerFromVault(mWeapons, id);
	}
	Characters::AIEnimy* Vault::GetEnimies(const int id) const noexcept
	{
		return GetItemPointerFromVault(mEnimies, id);
	}
	Characters::Class* Vault::GetClass(const int id) const noexcept
	{
		return GetItemPointerFromVault(mClasses, id);
	}

	void Vault::ClearTeam()
	{
		SaveLoad::JsonSaveLoad::DeleteSave();
		mTeam.reset();
	}
	Team::PlayerTeam* Vault::GetTeam() const
	{
		auto team = mTeam.get();
		return team;
	}

	void Vault::SaveTeam()
	{
		SaveLoad::JsonSaveLoad::Save(*mTeam);
	}

	void Vault::LoadTeamSave()
	{
		mTeam = std::make_shared<Team::PlayerTeam>(SaveLoad::JsonSaveLoad::LoadFileByName<Team::PlayerTeam>("PlayerSave.json"));
	}

	Team::PlayerTeam* Vault::CreateTeam()
	{

		if (mTeam == nullptr)
		{
			mTeam = std::make_shared<Team::PlayerTeam>();
		}

		return mTeam.get();
	}

	std::vector<const char*> Vault::GetWeaponList()
	{
		std::vector<const char*> nameList;

		for (const auto& w : mWeapons)
		{
			nameList.push_back(w.second->name.c_str());
		}

		return nameList;
	}

	Characters::AIEnimy* Vault::GetRandomEnimy()
	{
		int rand = GetRandomValue( 0, mEnimies.size()-1);
		return GetEnimies(rand);
	}
	
	template<typename T>
	T* Vault::GetItemPointerFromVault(const std::map<const int, std::shared_ptr<T>>& map, const int id) const noexcept
	{
		auto search = map.find(id);
		if (search != map.end())
		{
			return search->second.get();
		}
		else
		{
			return nullptr;
		}
	}
	template<typename T>
	void Vault::PopulateMap(std::map<const int, std::shared_ptr<T>>& map)
	{
		map.clear();
		std::vector<const char*> files = std::vector<const char*>();

		SaveLoad::JsonSaveLoad::GetFilesInDirectory<T>(files);

		for (auto& f : files)
		{
			const T c = SaveLoad::JsonSaveLoad::LoadFileByName<T>(f);

			map.insert(std::make_pair(c.ID, std::make_shared<T>(c)));
		}
	}
}
