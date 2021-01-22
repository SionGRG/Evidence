#include "GameManager.h"
#include "IntroState.h"

namespace Ass02_pong
{
	GameManager::GameManager(int screenWidth, int screenHeight, std::string title)
	{
		_data->window.create(sf::VideoMode(screenWidth, screenHeight),
			title, sf::Style::Close | sf::Style::Titlebar);
		_data->machine.AddState(StateRef(new IntroState(this->_data)));
		this->Run();
	}

	void GameManager::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->_data->window.isOpen())
		{
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dT)
			{
				this->_data->machine.GetActiveSate()->HandleInput();
				this->_data->machine.GetActiveSate()->Update(dT);
				accumulator -= dT;
			}
			interpolation = accumulator / dT;
			this->_data->machine.GetActiveSate()->Render(interpolation);
		}
	}
}
