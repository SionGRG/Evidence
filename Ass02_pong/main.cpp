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
	operator sf::Vector2f () const
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

	void Init(sf::RenderWindow& window, sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY) override
	{
		spr.setTexture(tex, true);
		//Hint: spr.setTextureRect(sf::IntRect{ 105, 5, 40, 40 });
		spr.setTextureRect(sf::IntRect{ batTexPosX, batTexPosY, batTexWidth, batTexHeight });
		//Hint: spr.setOrigin(20, 20);
		float batOrgX = batTexWidth / 2;			// set origin().x to the center of the texture
		float batOrgY = batTexHeight / 2;			// set origin().y to the center of the texture
		spr.setOrigin(batOrgX, batOrgY);
		//Hint: spr.setPosition(window.getSize().x * 0.5f, window.getSize().y * 0.5f);
		spr.setPosition(window.getSize().x * batPosX, window.getSize().y * batPosY);

		// Get random numbers for the ball movement
		srand(time(NULL));
	}

	void Reset(sf::RenderWindow& window)
	{
		spr.setPosition(window.getSize().x * 0.5f, window.getSize().y * 0.5f);
		ChangeXDirection();
	}

	void ChangeXDirection()
	{
		xDir *= -1;		// Change the direction of the ball in the x direction
	}
	float ChangeYDirection(sf::RenderWindow& window, float &cDirY)
	{
		// Check for hitting walls
		if (spr.getPosition().y < (window.getSize().y * 0) + spr.getOrigin().y)
		{
			cDirY = cDirY * -1;				// bounce the ball off the wall
			return cDirY;
		}
		if ((spr.getPosition().y + spr.getOrigin().y) > window.getSize().y)
		{
			cDirY = cDirY * -1;				// bounce the ball off the wall
			return cDirY;
		}
	}
	
	void Movement(sf::RenderWindow& window, float dT)
	{
		// Move the ball in the random position
		xVel = GetRandomNumber(2, -2);
		yVel = GetRandomNumber(2, -2);		

		ChangeYDirection(window, yDir);

		// Simulation
		vel = Vec2{ xDir * xVel * SPEED , yDir * yVel * SPEED };
		Vec2 pos{ spr.getPosition() };
		pos += vel * dT;
		
		spr.setPosition(pos);
	}

	void Update(sf::RenderWindow& window, float dT) override
	{
		Movement(window, dT);
	}
	void Render(sf::RenderWindow& window, float dT) override
	{
		Obj2D::Render(window, dT);
		// Fire trails
		// Sparkles
	}
};

class Bat : public Obj2D
{
public:
	// Controls
	sf::Keyboard::Key moveUp;
	sf::Keyboard::Key moveDown;

	void Init(sf::RenderWindow& window, sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY)
	{
		spr.setTexture(tex, true);
		//Hint: example: spr.setTextureRect(sf::IntRect{ 4, 5, 42, 140 });
		spr.setTextureRect(sf::IntRect{ batTexPosX, batTexPosY, batTexWidth, batTexHeight });
		//Hint: example: spr.setOrigin(21, 70);
		float batOrgX = batTexWidth/2;					// set origin().x to the center of the texture
		float batOrgY = batTexHeight/2;					// set origin().y to the center of the texture
		spr.setOrigin(batOrgX, batOrgY);
		//Hint: example: spr.setPosition(window.getSize().x * 0.05f, window.getSize().y * 0.5f);
		spr.setPosition(window.getSize().x * batPosX, window.getSize().y * batPosY);
	}

	void Movement(sf::RenderWindow& window, float dT)
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
			if ((spr.getPosition().y - 13) >= (window.getSize().y - spr.getOrigin().y))
				SPEED = 0;					// Stop the bat if it reaches to the bottom of the screen
			else
				SPEED = SPEED;
			vel = Vec2{ 0, SPEED };
		}
	}
	void Update(sf::RenderWindow& window, float dT)
	{		
		Movement(window, dT);
		// Simulation
		Vec2 pos{ spr.getPosition() };
		pos += vel * dT;

		spr.setPosition(pos);
		
	}
	void Render(sf::RenderWindow& window, float dT) override
	{
		Obj2D::Render(window, dT);
	}
};

class Game
{
private:

public:
	Ball ball;
	Bat bat1;
	Bat bat2;

	void Init(sf::RenderWindow& window, sf::Texture& tex)
	{

		// Ball
		ball.Init(window, tex, 105, 5, 40, 40, 0.5f, 0.5f);

		// Players
		bat1.Init(window, tex, 4, 5, 42, 140, 0.05f, 0.5f);
		bat2.Init(window, tex, 54, 5, 42, 140, 0.95f, 0.5f);
	}


	void Score(sf::RenderWindow& window, float dT)
	{

	}
	void Record(sf::RenderWindow& window, float dT)
	{
		// Record player score and reset the ball position goes the beyond the player's bat
		if (ball.spr.getPosition().x < (window.getSize().x * 0) + ball.spr.getOrigin().x)
		{
			Score(window, dT);
			ball.Reset(window);
		}
		if ((ball.spr.getPosition().x + ball.spr.getOrigin().x) > window.getSize().x)
		{
			Score(window, dT);
			ball.Reset(window);
		}
	}

	void controls()
	{
		// set the player controls
		//player 1
		bat1.moveUp = sf::Keyboard::W;
		bat1.moveDown = sf::Keyboard::S;
		//player 2
		bat2.moveUp= sf::Keyboard::Up;
		bat2.moveDown = sf::Keyboard::Down;
	}

	void Bounce(Bat bBat1, Bat bBat2)
	{
		// Check for hitting bat
		if ((ball.spr.getPosition().x - ball.spr.getOrigin().x) < bBat1.spr.getPosition().x &&				// ball has gone too far right of the player's bat
			(ball.spr.getPosition().y) < bBat1.spr.getPosition().y + bBat1.spr.getOrigin().y &&			
			(ball.spr.getPosition().y) > bBat1.spr.getPosition().y - bBat1.spr.getOrigin().y)				// ball is in the height range of the player's bat
		{
			ball.ChangeXDirection();
		}
		else if ((ball.spr.getPosition().x + ball.spr.getOrigin().x) > bBat2.spr.getPosition().x &&			// ball has gone too far right of the player's bat
			(ball.spr.getPosition().y) < bBat2.spr.getPosition().y + bBat2.spr.getOrigin().y &&			
			(ball.spr.getPosition().y) > bBat2.spr.getPosition().y - bBat2.spr.getOrigin().y)				// ball is in the height range of the player's bat
		{
			ball.ChangeXDirection();
		}
	}

	void Update(sf::RenderWindow& window, float dT)
	{
		controls();
		// Updates
		ball.Update(window, dT);
		bat1.Update(window, dT);
		bat2.Update(window, dT);

		// Bounce the ball back
		Bounce(bat1, bat2);
		// Record player score
		Record(window, dT);
	}

	void Render(sf::RenderWindow& window, float dT)
	{
		// Renders
		ball.Render(window, dT);
		bat1.Render(window, dT);
		bat2.Render(window, dT);
	}
};

//****************************************************************************
int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Ass02_Pong");

	sf::Texture texPong;
	if (!texPong.loadFromFile("data/pongSprites.png"))
		assert(false);

	Game game;
	game.Init(window, texPong);
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float elapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		// Updates
		game.Update(window, elapsedTime);
		window.clear();
		
		// Renders
		game.Render(window, elapsedTime);

		window.display();
	}
	return EXIT_SUCCESS;
}