#pragma once

#include <SFML/Graphics.hpp>

//a circular clocks demo 
class Game
{
private:
	sf::Texture texAnaFace;		//texture for analogue clock face	
	sf::Texture texAnaHands;	//texture for analogue clock hands
	float baseRotation = 0;		//all rotation keyed to this variable (degrees)
	float clockAng = 0;
	float rndOffset = 0, rndOffset2 = 0; //use to generate two offsets to clock hand rotations

	/*
	Render one clock face
	window - reference to main window
	pos - where to centre the clock on the screen
	angle - angle of ahands on clock
	sclae - size of clock (and hands)
	*/
	void RenderClockFace(sf::RenderWindow& window, sf::Vector2f& pos, float angle, float scale);

public:
	
	//run once at start
	void Initialise();

	/*
	* Call every frame to update logic
	* dT - elapsed time for one update
	*/
	void Update(float dT);

	/*
	Main render call for the game
		Draws 20 clock faces
	window - reference to render window
	*/
	void Render(sf::RenderWindow& window);

	void Keyboard(sf::Keyboard::Key code);
};


