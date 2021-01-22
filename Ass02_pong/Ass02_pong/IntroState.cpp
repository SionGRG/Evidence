#include "AssetManager.h"
#include "IntroState.h"
#include "MainMenuState.h"
#include <sstream>
#include "Definitions.h"
#include <iostream>

namespace Ass02_pong
{
	IntroState::IntroState(GameDataRef data) : _data(data)
	{

	}

	void IntroState::Init()
	{
		/* Load textures */
		_data->assets.LoadTexture("Intro Background", INTRO_SCENE_BACKGROUND_FILEPATH);
		/* set textures to their respective variables */
		_background.setTexture(this->_data->assets.GetTexture("Intro Background"));
		/* Scale the textures to the screen size */
		float XScale = SCREEN_WIDTH / _background.getGlobalBounds().width;
		float YScale = SCREEN_HEIGHT / _background.getGlobalBounds().height;
		_background.setScale(XScale, YScale);
		/* Center the textures */
		_background.setPosition((SCREEN_WIDTH / 2) - (_background.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_background.getGlobalBounds().height / 2));
	}

	void IntroState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
		}
	}
	
	void IntroState::Update(float dT)
	{
		if (_clock.getElapsedTime().asSeconds() > INTRO_SHOW_TIME)
		{
			_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void IntroState::Render(float dT)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.display();
	}
}