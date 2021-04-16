#include "GameObj.h"

namespace Ass02_pong
{
	//Ball	*****************************************************************

	void Ball::Init(sf::Texture& tex, int ballTexPosX, int ballTexPosY, int ballTexWidth, int ballTexHeight, float ballPosX, float ballPosY)
	{
		spr.setTexture(tex, true);
		//Hint: spr.setTextureRect(sf::IntRect{ 105, 5, 40, 40 });
		spr.setTextureRect(sf::IntRect{ ballTexPosX, ballTexPosY, ballTexWidth, ballTexHeight });
		//Hint: spr.setOrigin(20, 20);
		float batOrgX = ballTexWidth / 2;			// set origin().x to the center of the texture
		float batOrgY = ballTexHeight / 2;			// set origin().y to the center of the texture
		spr.setOrigin(batOrgX, batOrgY);
		//Hint: spr.setPosition(window.getSize().x * 0.5f, window.getSize().y * 0.5f);
		spr.setPosition(SCREEN_WIDTH * ballPosX, SCREEN_HEIGHT * ballPosY);

		// Get random numbers for the ball movement
		srand(time(NULL));
	}

	void Ball::Reset()
	{
		spr.setPosition(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
		ChangeXDirection();
	}

	void Ball::ChangeXDirection()
	{
		xDir *= -1;		// Change the direction of the ball in the x direction
	}
	float Ball::ChangeYDirection(float& cDirY)
	{
		// Check for hitting walls
		if (spr.getPosition().y < (SCREEN_HEIGHT * 0) + spr.getOrigin().y)
		{
			cDirY = cDirY * -1;				// bounce the ball off the wall
			return cDirY;
		}
		if ((spr.getPosition().y + spr.getOrigin().y) > SCREEN_HEIGHT)
		{
			cDirY = cDirY * -1;				// bounce the ball off the wall
			return cDirY;
		}
	}

	void Ball::Movement(float dT)
	{
		// Move the ball in the random position
		xVel = GetRandomNumber(1, -1);
		yVel = GetRandomNumber(1, -1);

		ChangeYDirection(yDir);

		// Simulation
		vel = Vec2{ xDir * xVel * SPEED , yDir * yVel * SPEED };
		Vec2 pos{ spr.getPosition() };
		pos += vel * dT;

		spr.setPosition(pos);
	}

	void Ball::Update(float dT)
	{
		Movement(dT);
	}
	void Ball::Render(float dT)
	{
		Obj2D::Render(dT);
		// Fire trails
		// Sparkles
	}


	//Bat	*****************************************************************

	void Bat::Init(sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY)
	{
		spr.setTexture(tex, true);
		//Hint: example: spr.setTextureRect(sf::IntRect{ 4, 5, 42, 140 });
		spr.setTextureRect(sf::IntRect{ batTexPosX, batTexPosY, batTexWidth, batTexHeight });
		//Hint: example: spr.setOrigin(21, 70);
		float batOrgX = batTexWidth / 2;					// set origin().x to the center of the texture
		float batOrgY = batTexHeight / 2;					// set origin().y to the center of the texture
		spr.setOrigin(batOrgX, batOrgY);
		//Hint: example: spr.setPosition(window.getSize().x * 0.05f, window.getSize().y * 0.5f);
		spr.setPosition(SCREEN_WIDTH * batPosX, SCREEN_HEIGHT * batPosY);
	}

	void Bat::Movement(float dT)
	{
		// Bat movement control
		float SPEED = 350;
		if (sf::Keyboard::isKeyPressed(moveUp))
		{
			if ((spr.getPosition().y + 13) <= spr.getOrigin().y)
				SPEED = 0;					// Stop the bat if it reaches to the top of the screen
			else
				SPEED = SPEED;
			vel = Vec2{ 0, -SPEED };
		}
		else if (sf::Keyboard::isKeyPressed(moveDown))
		{
			if ((spr.getPosition().y - 13) >= (SCREEN_HEIGHT - spr.getOrigin().y))
				SPEED = 0;					// Stop the bat if it reaches to the bottom of the screen
			else
				SPEED = SPEED;
			vel = Vec2{ 0, SPEED };
		}
	}
	void Bat::Update(float dT)
	{
		Movement(dT);
		// Simulation
		Vec2 pos{ spr.getPosition() };
		pos += vel * dT;

		spr.setPosition(pos);

	}
	void Bat::Render(float dT)
	{
		Obj2D::Render(dT);
	}
}