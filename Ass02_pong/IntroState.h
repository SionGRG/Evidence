#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameManager.h"

namespace Ass02_pong
{
	class IntroState : public State
	{
	public: 
		IntroState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dT);
		void Render(float dT);
	
	private:
		GameDataRef _data;

		sf::Clock _clock;
		
		sf::Sprite _background;
	};
}