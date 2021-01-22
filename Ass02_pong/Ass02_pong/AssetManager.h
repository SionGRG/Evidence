#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Ass02_pong
{
	class AssetManager
	{
	public:
		AssetManager() {}
		~AssetManager() {}

		void LoadTexture(std::string name, std::string fileName);
		sf::Texture& GetTexture(std::string name);
		void LoadFont(std::string name, std::string fileName);
		sf::Font& GetFont(std::string name);
		void LoadSound(std::string name, std::string fileName);
		sf::SoundBuffer& GetSound(std::string name);

	private:
		std::map<std::string, sf::Texture> texturesMap;
		std::map<std::string, sf::Font> fontsMap;
		std::map<std::string, sf::SoundBuffer> soundsMap;
	};
}