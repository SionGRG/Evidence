#include "MainMenuState.h"
#include "Game.h"
#include <sstream>
#include "Definitions.h"
#include <iostream>

namespace Ass02_pong
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		/* Load textures */
		_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		
		/* set textures to their respective variables */
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		
		/* Scale the textures to the screen size */
		float XScale = SCREEN_WIDTH / _background.getGlobalBounds().width;
		float YScale = SCREEN_HEIGHT / _background.getGlobalBounds().height;
		_background.setScale(XScale, YScale);

		/* Center the textures */
		_background.setPosition((SCREEN_WIDTH/2) - (_background.getGlobalBounds().width/2), 
			(SCREEN_HEIGHT / 2) - (_background.getGlobalBounds().height / 2));
		_title.setPosition((SCREEN_WIDTH/2) - (_title.getGlobalBounds().width/2), 
			_title.getGlobalBounds().height / 2);
		_playButton.setPosition((SCREEN_WIDTH/2) - (_playButton.getGlobalBounds().width/2), 
			(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
	}

	void MainMenuState::HandleInput()
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
				_data->machine.AddState(StateRef(new Game(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dT)
	{

	}

	void MainMenuState::Render(float dT)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_playButton);
		_data->window.display();
	}
}