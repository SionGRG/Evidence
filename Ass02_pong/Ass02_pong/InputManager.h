#pragma once

#include <SFML/Graphics.hpp>

namespace Ass02_pong
{
	class InputManager
	{
	public:
		InputManager(){}
		~InputManager(){}

		/* Mouse Click */
		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);

	};
}