#include <assert.h>

#include "Game.h"

using namespace std;


//********************************************
//where it all starts 
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Clock final submission");

////////////////////////////////////////////////////////////
	//initialsation - one time
	Time time;


	Time time3(1, 1, 1);
	time3.displayTime();
	cout << "\n";
	Time time4(3723);
	time4.displayTime();
	cout << "\n";
	Time time5("04:05:06");
	time5.displayTime();

	{
		Time t1;	//line1
		t1.setTime(6, 7, 8);
		Time t2(t1); 	//line2
		Time t3 = t1; 	//line3
	}

	{
		Time t4(12, 2, 3);
		cout << "\nBefore calling isPM";
		if (isPM(t4)) 	//line4
			cout << "\nt4 is in the afternoon";
		cout << "\nAfter calling isPM";
	}

	{
		Time t1; 	//line7
		cout << "\nBefore calling getCurrentTime";
		t1 = getCurrentTime();	//line8
		cout << "\nAfter calling getCurrentTime";
	}

	{
		cout << "\nBefore calling getCurrentTime";
		Time t5(getCurrentTime());	//line9
		cout << "\nAfter calling getCurrentTime";
	}

	Time t;
	const Time ct;
	/*
	cout << t.hrs_;

	cout << t.toSeconds();

	readInTime();
	*
	cout << t.displayTime();
	*/
	//cout << t.getHours;

	//ct.readInTime();



	cout << "\n\n__ Time t1\n";
	Time t1;
	t1.displayTime();

	cout << "\n\n__ cout << t1.getHours()\n";
	cout << t1.getHours();

	cout << "\n\n__ t1.displayTime()\n";
	t1.displayTime();

	cout << "\n\n__ t1.setTime(1,2,3)\n";
	t1.setTime(1, 2, 3);
	t1.displayTime();

	cout << "\n\n__ Time t2(t1)\n";
	Time t2(t1);
	t2.displayTime();

	cout << "\n\n__ t1.readInTime()\n";
	t1.readInTime();
	t1.displayTime();
//////////////////////////////////////////////////////////////

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
