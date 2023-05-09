#pragma once
#include <fstream>
#include <filesystem>
#include <direct.h>
#include "raylib.h"
#include "thirdparty/nlohmann/json.hpp"
using json = nlohmann::json;

namespace SaveLoad
{
	class JsonSaveLoad
	{
	private:
		 static inline const std::string type = ".json";

	public:
		//folder Locations
		static inline const std::string classes = "resources/Classes/";
		static inline const std::string weapons = "resources/Weapons/";
		static inline const std::string ai = "resources/AI/";
		static inline const std::string characters = "resources/Characters/";
		static inline const std::string saves = "resources/Saves/";

		template<typename T>
		static inline void Save(const T& file)
		{
			json j = file;
			const char* folder = GetFolder<T>().c_str();

			if (!DirectoryExists(folder))
			{
				_mkdir(folder);
			}
			
			std::ofstream filetarget(folder + file.name + type);
			filetarget << j;
		}

		static inline void DeleteSave()
		{
			if (DoesSaveExist())
			{
				std::filesystem::remove_all(saves);
			}
		}

		static inline bool DoesSaveExist()
		{
			return DirectoryExists(saves.c_str());
		}

		template<typename T>
		static inline T LoadFilesInFolder()
		{
			T file;
			const char* folder = GetFolder(file);

			std::fstream stream(file);

			auto file = json::parse(stream);

			return file;
		}

		template<typename T>
		static inline T LoadFileByName(const char* str)
		{
			T file;
			char* end = "";
			if (!IsFileExtension(str, type.c_str()))
			{
				//I want it to be = type.c_str() but I got an error and im just not in the mood to deal with it.
				end = ".json";
			}
			const std::string folder = GetFolder<T>() + str + end;

			std::fstream stream(folder);

			json j = json::parse(stream);

			file = j;

			return file;
		}

		static inline void GetFilesInDirectory(std::vector<const char*>& out, const std::string& directory)
		{
			out.clear();
			int filecount = 0;
			auto files = GetDirectoryFiles(directory.c_str(), &filecount);

			for (int i = 0; i < filecount; ++i)
			{
				if (!IsFileExtension(files[i],type.c_str())) continue;

				out.push_back(files[i]);
			}
		}

		template<typename T>
		static inline void GetFilesInDirectory(std::vector<const char*>& out)
		{
			GetFilesInDirectory(out, GetFolder<T>());
		}

	private:
		template<typename T>
		static inline const std::string& GetFolder()
		{
			//Sorts out specific folder that contains the coresponding json;
			if (std::is_convertible<T, Characters::Class>())
			{
				return classes;
			}
			else if (std::is_convertible<T, Weapons::Weapon>())
			{
				return weapons;
			}
			else if (std::is_convertible<T, Characters::AIEnimy>())
			{
				return ai;
			}
			else if (std::is_convertible<T, Characters::Character>())
			{
				return characters;
			}
			else
			{
				return saves;
			}
		}
	
	};
}
