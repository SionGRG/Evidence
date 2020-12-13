#include <assert.h>

#include "Game.h"

using namespace std;


//********************************************
//where it all starts 
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Clock final submission");

	//initialsation - one time
	Game game;
	game.Initialise();

	// Start the game loop 
	sf::Clock clock;
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				else
					game.Keyboard(event.key.code);
			}
		}


		float dT = clock.getElapsedTime().asSeconds();
		clock.restart();
		
		// Clear screen
		window.clear();

		//logical update stuff
		game.Update(dT);

		//rendering
		game.Render(window);

		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}
