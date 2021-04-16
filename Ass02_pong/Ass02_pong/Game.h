#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <stdlib.h>
#include <ctime>
#include "Definitions.h"
#include "State.h"
#include "GameManager.h"
#include "GameObj.h"

namespace Ass02_pong
{
	class Game : public State
	{
	public:
		Game(GameDataRef data);
		//~Game();

		void Init();
		void Score(sf::Font font);
		void Record();
		void HandleInput();
		void Bounce(Bat bBat1, Bat bBat2);
		void GameOver();
		void Update(float dT);
		void Render(float dT);
	private:
		GameDataRef _data;
		//Sprites
		sf::Sprite _background;
		sf::Texture _pongSheet;
		//Fonts
		sf::Font _fontAirstream;
		// Objects
		Wall wallT;
		Wall wallB;
		Ball ball;
		Bat bat1;
		Bat bat2;
		int p1Score = 0;
		int p2Score = 0;
		const int maxScore = MAX_SCORE;
	};
}
