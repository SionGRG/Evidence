#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameManager.h"

namespace Ass02_pong
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dT);
		void Render(float dT);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _title;
		sf::Sprite _mainMenuButton;
		sf::Sprite _playButton;
	};
}