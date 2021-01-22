#include <sstream>
#include <iostream>
#include "Game.h"

namespace Ass02_pong
{
	Game::Game(GameDataRef data) : _data(data)
	{

	}

	void Game::Init()
	{
		// Background
		_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));
		// Pong Spritesheet
		_data->assets.LoadTexture("Pong Sprite Sheet", SPRITESHEET_PONG_FILEPATH);
		_pongSheet = this->_data->assets.GetTexture("Pong Sprite Sheet");
		// Font Airstream
		_data->assets.LoadFont("Airstream Font", FONT_AIRSTREAM_FILEPATH);
		_fontAirstream = this->_data->assets.GetFont("Airstream Font");

		// Ball
		ball.Init(_pongSheet, 105, 5, 40, 40, 0.5f, 0.5f);

		// Players
		bat1.Init(_pongSheet, 4, 5, 42, 140, 0.05f, 0.5f);
		bat2.Init(_pongSheet, 54, 5, 42, 140, 0.95f, 0.5f);

	}

	void Game::Score(sf::Font font)
	{
		sf::Text txtScore;									// score text											
		sf::Text txtP1Score;								// Player 1 score text
		sf::Text txtP2Score;								// Player 2 score text

		float scorePos = 40;								// half distance between player 1 and player 2 

		/* score text */
		txtScore.setFont(font);												// select the font
		txtScore.setString("SCORE");										// set the string to display
		txtScore.setCharacterSize(48);										// set the character size		
		txtScore.setFillColor(sf::Color::White);							// set the color
		txtScore.setStyle(sf::Text::Bold);									// set the text style
		// center score text
		sf::FloatRect scoreTxtRect = txtScore.getLocalBounds();
		txtScore.setOrigin(scoreTxtRect.left + scoreTxtRect.width / 2.0f,
			scoreTxtRect.top + scoreTxtRect.height / 2.0f);					// set score origin to the center of the score text
		txtScore.setPosition(SCREEN_WIDTH / 2,
			SCREEN_HEIGHT * .025f);											// set the position

		/* Player 1 score */
		txtP1Score.setFont(font);											// select the font
		txtP1Score.setString(to_string(p1Score));							// set the string to display
		txtP1Score.setCharacterSize(72);									// set the character size		
		txtP1Score.setFillColor(sf::Color::Red);							// set the color
		txtP1Score.setStyle(sf::Text::Bold);								// set the text style
		// center score text
		sf::FloatRect p1TxtRect = txtP1Score.getLocalBounds();
		txtP1Score.setOrigin(p1TxtRect.left + p1TxtRect.width / 2.0f,
			p1TxtRect.top + p1TxtRect.height / 2.0f);						// set score origin to the center of the score text
		txtP1Score.setPosition((SCREEN_WIDTH / 2) - scorePos,
			SCREEN_HEIGHT * .1f);											// set the position

		/* Player 2 score */
		txtP2Score.setFont(font);											// select the font
		txtP2Score.setString(to_string(p2Score));							// set the string to display
		txtP2Score.setCharacterSize(72);									// set the character size		
		txtP2Score.setFillColor(sf::Color::Blue);							// set the color
		txtP2Score.setStyle(sf::Text::Bold);								// set the text style
		// center score text
		sf::FloatRect p2TxtRect = txtP2Score.getLocalBounds();
		txtP2Score.setOrigin(p2TxtRect.left + p2TxtRect.width / 2.0f,
			p2TxtRect.top + p2TxtRect.height / 2.0f);						// set score origin to the center of the score text
		txtP2Score.setPosition((SCREEN_WIDTH / 2) + scorePos,
			SCREEN_HEIGHT * .1f);											// set the position

		// Draw texts
		_data->window.draw(txtScore);
		_data->window.draw(txtP1Score);
		_data->window.draw(txtP2Score);
	}

	void Game::Record()
	{
		// Record player score and reset the ball position goes the beyond the player's bat
		if (ball.spr.getPosition().x < (SCREEN_WIDTH * 0) + ball.spr.getOrigin().x)
		{
			++p2Score;
			ball.Reset();
		}
		if ((ball.spr.getPosition().x + ball.spr.getOrigin().x) > SCREEN_WIDTH)
		{
			++p1Score;
			ball.Reset();
		}
		if (p1Score == maxScore || p2Score == maxScore)
		{
			p1Score = 0;
			p2Score = 0;
			GameOver();
		}
	}

	void Game::GameOver()
	{
		_data->machine.AddState(StateRef(new GameOverState(_data)), false);
	}

	void Game::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
		}

		// set the player controls
		//player 1
		bat1.moveUp = sf::Keyboard::W;
		bat1.moveDown = sf::Keyboard::S;
		//player 2
		bat2.moveUp = sf::Keyboard::Up;
		bat2.moveDown = sf::Keyboard::Down;
	}

	void Game::Bounce(Bat bBat1, Bat bBat2)
	{
		// Check for hitting bat
		if ((ball.spr.getPosition().x - ball.spr.getOrigin().x) < bBat1.spr.getPosition().x &&				// ball has gone too far right of the player's bat
			(ball.spr.getPosition().y) < bBat1.spr.getPosition().y + bBat1.spr.getOrigin().y &&
			(ball.spr.getPosition().y) > bBat1.spr.getPosition().y - bBat1.spr.getOrigin().y)				// ball is in the height range of the player's bat
		{
			ball.ChangeXDirection();
		}
		else if ((ball.spr.getPosition().x + ball.spr.getOrigin().x) > bBat2.spr.getPosition().x &&			// ball has gone too far right of the player's bat
			(ball.spr.getPosition().y) < bBat2.spr.getPosition().y + bBat2.spr.getOrigin().y &&
			(ball.spr.getPosition().y) > bBat2.spr.getPosition().y - bBat2.spr.getOrigin().y)				// ball is in the height range of the player's bat
		{
			ball.ChangeXDirection();
		}
	}

	void Game::Update(float dT)
	{
		// Controls
		HandleInput();
		// Updates
		ball.Update(dT);
		bat1.Update(dT);
		bat2.Update(dT);

		// Bounce the ball back
		Bounce(bat1, bat2);
		// Record player score and Reset score if it reaches max score
		Record();
	}

	void Game::Render(float dT)
	{
		_data->window.clear();
		_data->window.draw(_background);
		// Object Renders
			//ball.Render(dT);
			//bat1.Render(dT);
			//bat2.Render(dT);
		_data->window.draw(ball.spr);
		_data->window.draw(bat1.spr);
		_data->window.draw(bat2.spr);
		// Score Renders
		Score(_fontAirstream);
		_data->window.display();
	}
}