#pragma once

#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace Ass02_pong
{
	struct GameData
	{
		StateMachine			machine;
		sf::RenderWindow		window;
		AssetManager			assets;
		InputManager			input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class GameManager
	{
	public:
		GameManager(int screenWidth, int screenHeight, std::string title);

	private:
		const float dT = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();

		void Run();
	};
}