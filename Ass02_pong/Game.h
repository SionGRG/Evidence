#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <ctime>

using namespace std;

class Vec2
{
public:
	float x, y;

	Vec2()
		:x(0), y(0)
	{}
	Vec2(float _x, float _y)
		:x(_x), y(_y)
	{}
	Vec2(const sf::Vector2f& rhs)
		:x(rhs.x), y(rhs.y)
	{}
	Vec2 operator*(float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	void operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}
	operator sf::Vector2f() const
	{
		sf::Vector2f tmp;
		tmp.x = x;
		tmp.y = y;
		return tmp;
	}
};

class Obj2D
{
public:
	sf::Sprite spr;
	Vec2 vel;

	virtual ~Obj2D() {}
	virtual void Render(sf::RenderWindow& window, float dT) = 0
	{
		window.draw(spr);
	}
	virtual void Update(sf::RenderWindow& window, float dT) = 0;
	/*	Build a texture and set sprite position
	float batTexPosX;		set the texture's rectangular x position value
	float batTexPosY;		set the texture's rectangular y position value
	float batTexWidth;		set the texture's rectangular width value
	float batTexHeight;		set the texture's rectangular height value
	float batPosX;			set the sprite's x position relative to the window size ie. a value that will be multiplied with the window size x value (must be between 0.f and 1.f)
	float batPosY;			set the sprite's y position relative to the window size ie. a value that will be multiplied with the window size y value (must be between 0.f and 1.f)
	*/
	virtual void Init(sf::RenderWindow& window, sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY) = 0;
};


class Ball : public Obj2D
{
private:
public:
	float xVel, yVel;
	float SPEED = 350;
	float xDir = 1;
	float yDir = 1;

	int GetRandomNumber(int high, int low)
	{
		return (rand() % high) + low;
	}
	void Init(sf::RenderWindow& window, sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY) override;
	void Reset(sf::RenderWindow& window);
	void ChangeXDirection();
	float ChangeYDirection(sf::RenderWindow& window, float& cDirY);
	void Movement(sf::RenderWindow& window, float dT);
	void Update(sf::RenderWindow& window, float dT) override;
	void Render(sf::RenderWindow& window, float dT) override;
};

class Bat : public Obj2D
{
public:
	// Controls
	sf::Keyboard::Key moveUp;
	sf::Keyboard::Key moveDown;

	void Init(sf::RenderWindow& window, sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY);
	void Movement(sf::RenderWindow& window, float dT);
	void Update(sf::RenderWindow& window, float dT);
	void Render(sf::RenderWindow& window, float dT) override;
};

class Game
{
private:

public:
	Ball ball;
	Bat bat1;
	Bat bat2;

	void Init(sf::RenderWindow& window, sf::Texture& tex);
	void Score(sf::RenderWindow& window, float dT);
	void Record(sf::RenderWindow& window, float dT);
	void controls();
	void Bounce(Bat bBat1, Bat bBat2);
	void Update(sf::RenderWindow& window, float dT);
	void Render(sf::RenderWindow& window, float dT);
	void RunGame();
};