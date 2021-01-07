#include "AssetManager.h"

namespace Ass02_pong
{
	/* Load Textures */
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->texturesMap[name] = tex;
		}
	}
	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return this->texturesMap.at(name);
	}

	/* Load Fonts */
	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->fontsMap[name] = font;
		}
	}
	sf::Font& AssetManager::GetFont(std::string name)
	{
		return this->fontsMap.at(name);
	}
	
	/* Load Sounds and audio */
	void AssetManager::LoadSound(std::string name, std::string fileName)
	{
		sf::SoundBuffer sound;

		if (sound.loadFromFile(fileName))
		{
			this->soundsMap[name] = sound;
		}
	}
	sf::SoundBuffer& AssetManager::GetSound(std::string name)
	{
		return this->soundsMap.at(name);
	}
}