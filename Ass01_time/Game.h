#pragma once

//--------include libraries
#include <SFML/Graphics.hpp>				//for SFML
#include <ctime>							//for time
#include <iostream>							//for cin >> and cout <<
#include <sstream>							//for string stream processing
#include <string>							//for string routines
#include <iomanip>							//for setw, setfill
using namespace std;


//--------Time class-------------
class Time {
public:
	Time();									//default constructor
	Time(const Time&);						//copy constructor

	Time(int h, int m, int s);				// bespoke contructor
	Time(long long);						// conversion constructor
	Time(const string& timeAsString);		// conversion constructor

	~Time();								//destructor
	int getHours() const;					//return a data member value, hrs_
	int getMinutes() const;					//return a data member value, mins_
	int getSeconds() const;					//return a data member value, secs_
	void setTime(int, int, int);			//set the time to 3 given values
	void readInTime();						//input time from user
	void displayTime() const;				//display in 00:00:00 digital clock format
private:
	int hrs_, mins_, secs_;
	long long toSeconds() const;			//return the time in seconds
};


// Other function definitions
bool isPM(const Time& t);

Time getCurrentTime();

//a circular clocks demo 
class Game
{
private:
	sf::Texture texAnaFace;					//texture for analogue clock face	
	sf::Texture texAnaHands;				//texture for analogue clock hands
	float baseRotation = 0;					//all rotation keyed to this variable (degrees)
	float clockAng = 0;
	float rndOffset = 0, rndOffset2 = 0;	//use to generate two offsets to clock hand rotations

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


