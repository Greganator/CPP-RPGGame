#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include "raygui.h"

namespace Screens::UI
{
	/// <summary>
	/// Getting the position on screen via a percentage
	/// </summary>
	/// <param name="width">1->0 percent position on screen</param>
	/// <param name="height">1->0 percent position on screen</param>
	inline Vector2 GetSceenPosFromPrecentage(const float width, const float height)
	{
		return Vector2{ GetScreenWidth() *std::clamp(width,0.f,1.f),GetScreenHeight() * std::clamp(height,0.f,1.f) };
	}

	inline Texture2D LoadTextureFromResources(const char* filename)
	{
		auto image = LoadImage(filename);
		auto texture = LoadTextureFromImage(image);
		UnloadImage(image);
		return texture;
	}

	inline void GetFilesDirectory(std::vector<const char*>& out, const std::string& directory, const char* extension)
	{
		out.clear();
		int filecount = 0;
		auto files = GetDirectoryFiles(directory.c_str(), &filecount);

		for (int i = 0; i < filecount; ++i)
		{
			//quick fix for wav files not working
			if (!IsFileExtension(files[i], extension) && !IsFileExtension(files[i], ".wav")) continue;

			out.push_back(files[i]);
		}
	}

	inline Texture2D LoadRandomFileFromDirectory(const std::string& path)
	{
		std::vector<const char*> files = std::vector<const char*>();
		GetFilesDirectory(files, path, ".png");
		return LoadTextureFromResources((path+files[GetRandomValue(0, files.size() - 1)]).c_str());
	}

	inline Texture2D LoadRandomTopBackground()
	{
		const std::string path = "resources/Art/Backgrounds/Top/";
		return LoadRandomFileFromDirectory(path);
	}

	inline Texture2D LoadRandomBottomBackground()
	{
		const std::string path = "resources/Art/Backgrounds/Bottom/";
		return LoadRandomFileFromDirectory(path);
	}

	inline void DrawBackgroundTexture(const Texture2D texture, const Color tint)
	{
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { 0, 0, GetScreenWidth(), GetScreenHeight()};
		Vector2 origin = { 0.0f, 0.0f };

		DrawTexturePro(texture, source, dest, origin, 0, tint);
	}
	inline void DrawValueBar(float x, float y, const float width, const float fill, const Color colour)
	{
		DrawRectangleLinesEx(Rectangle{x,y,width, 8 }, .5f, WHITE);
		DrawRectangleRec(Rectangle{x+2,y+2,(width*fill)-4,7},colour);
	}

	inline void LoadBackgroundMusic(const char* path, Music& music)
	{
		StopMusicStream(music);
		UnloadMusicStream(music);
		music = LoadMusicStream(path);
		SetMusicVolume(music, .4f);
		PlayMusicStream(music);
	}

	inline void LoadRandomBackgroundmusic(const std::string& path, Music& music)
	{
		std::vector<const char*> files = std::vector<const char*>();
		GetFilesDirectory(files, path, ".ogg");
		LoadBackgroundMusic((path + files[GetRandomValue(0, files.size() - 1)]).c_str(), music);
	}
}