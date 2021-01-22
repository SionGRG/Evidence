#include <sstream>
#include <iostream>
#include "Definitions.h"
#include "GameOverState.h"
#include "MainMenuState.h"
#include "Game.h"

namespace Ass02_pong
{
	GameOverState::GameOverState(GameDataRef data) : _data(data)
	{

	}

	void GameOverState::Init()
	{
		/* Load textures */
		_data->assets.LoadTexture("GameOver Background", GAMEOVER_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Game Title", GAMEOVER_TITLE_FILEPATH);
		_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		_data->assets.LoadTexture("Main Menu Button", MAIN_MENU_BUTTON_FILEPATH);
		_data->assets.LoadTexture("Quit Button", QUIT_BUTTON_FILEPATH);

		/* set textures to their respective variables */
		_background.setTexture(this->_data->assets.GetTexture("GameOver Background"));
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		_mainMenuButton.setTexture(this->_data->assets.GetTexture("Main Menu Button"));
		_quitButton.setTexture(this->_data->assets.GetTexture("Quit Button"));

		/* Scale the textures to the screen size */
		float XScale = SCREEN_WIDTH / _background.getGlobalBounds().width;
		float YScale = SCREEN_HEIGHT / _background.getGlobalBounds().height;
		_background.setScale(XScale, YScale);

		/* Center the textures */
		_background.setPosition((SCREEN_WIDTH / 2) - (_background.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_background.getGlobalBounds().height / 2));
		_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2),
			_title.getGlobalBounds().height / 2);
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2.5) - (_playButton.getGlobalBounds().height / 2));
		_mainMenuButton.setPosition((SCREEN_WIDTH / 2) - (_mainMenuButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_mainMenuButton.getGlobalBounds().height / 2));
		_quitButton.setPosition((SCREEN_WIDTH / 2) - (_quitButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 1.65) - (_quitButton.getGlobalBounds().height / 2));
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
			if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window))
			{
				_data->machine.AddState(StateRef(new Game(_data)), false);
			}
			if (_data->input.IsSpriteClicked(_mainMenuButton, sf::Mouse::Left, _data->window))
			{
				_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
			if (_data->input.IsSpriteClicked(_quitButton, sf::Mouse::Left, _data->window))
			{
				_data->window.close();
			}
		}
	}

	void GameOverState::Update(float dT)
	{

	}

	void GameOverState::Render(float dT)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_mainMenuButton);
		_data->window.draw(_playButton);
		_data->window.draw(_quitButton);
		_data->window.display();
	}
}