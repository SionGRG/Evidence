#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameManager.h"

namespace Ass02_pong
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dT);
		void Render(float dT);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _playButton;
	};
}