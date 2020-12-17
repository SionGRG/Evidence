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
	virtual void Init(sf::RenderWindow& window, sf::Texture& tex) = 0;
};

class Ball : public Obj2D
{
private:
public:
	float xVel, yVel;
	float SPEED = 100;
	float xDir = 1;
	float yDir = 1;
	bool cDir = false;

	int GetRandomNumber(int high, int low)
	{
		return (rand() % high) + low;
	}

	void Init(sf::RenderWindow& window, sf::Texture& tex) override
	{
		spr.setTexture(tex, true);
		spr.setTextureRect(sf::IntRect{ 105, 5, 40, 40 });
		spr.setOrigin(20, 20);
		spr.setPosition(window.getSize().x * 0.5f, window.getSize().y * 0.5f);

		// Get random numbers for the ball movement
		srand(time(NULL));
	}

	void Reset(sf::RenderWindow& window)
	{
		spr.setPosition(window.getSize().x * 0.5f, window.getSize().y * 0.5f);
	}

	void Score(sf::RenderWindow& window, float dT)
	{

	}
	void Record(sf::RenderWindow& window, float dT)
	{	
		// Record player score and reset the ball position
		if (spr.getPosition().x < (window.getSize().x * 0) + spr.getOrigin().x)
		{
			Score(window, dT);
			Reset(window);
		}
		if ((spr.getPosition().x + spr.getOrigin().x) > window.getSize().x)
		{
			Score(window, dT);
			Reset(window);
		}
	}
	/*
	float ChangeXDirection(float cDirX)
	{
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			cDirX = cDirX * -1;
			return cDirX;
	}
	*/
	float ChangeXDirection(float cDirX)
	{
		cDirX *= -1;
		return cDirX;
		
	}

	float ChangeYDirection(sf::RenderWindow& window, float &cDirY)
	{
		// Check for hitting walls
		if (spr.getPosition().y < (window.getSize().y * 0) + spr.getOrigin().y)
		{
			cDirY = cDirY * -1;
			return cDirY;
		}
		if ((spr.getPosition().y + spr.getOrigin().y) > window.getSize().y)
		{
			cDirY = cDirY * -1;
			return cDirY;
		}
	}
	
	void Movement(sf::RenderWindow& window, float dT)
	{
		// Move the ball in the random position
		xVel = GetRandomNumber(2, -2);
		yVel = GetRandomNumber(2, -2);		

		ChangeYDirection(window, yDir);
		if (cDir = true)
			ChangeXDirection(xDir);

		// Simulation
		vel = Vec2{ xDir * xVel * SPEED , yDir * yVel * SPEED };
		Vec2 pos{ spr.getPosition() };
		pos += vel * dT;

		spr.setPosition(pos);
	}

	void Update(sf::RenderWindow& window, float dT) override
	{
		Movement(window, dT);
		Record(window, dT);
	}
	void Render(sf::RenderWindow& window, float dT) override
	{
		Obj2D::Render(window, dT);
		// Fire trails
		// Sparkles
	}
};

class Bat1 : public Obj2D
{
public:
	
	Ball* pMyBall;
	/*
	void Init(sf::RenderWindow& window, sf::Texture& tex, Ball& ball)
	{
		pMyBall = &ball;
		Init(window, tex);
	}*/

	void Init(sf::RenderWindow& window, sf::Texture& tex)
	{
		spr.setTexture(tex, true);
		//spr.setTextureRect(sf::IntRect{ 105, 103, 143, 48 });
		spr.setTextureRect(sf::IntRect{ 4, 5, 42, 140 });
		spr.setOrigin(21, 70);
		//spr.setPosition(window.getSize().x * 0.95f, window.getSize().y * 0.5f);
		spr.setPosition(window.getSize().x * 0.025f, window.getSize().y * 0.5f);
	}

	bool Bounce(Vec2 oBPos, Vec2 oBOrg)
	{
		// Check for hitting bat
		/*if (oBPos.x < (pMyBall->spr.getPosition().x)
			&& oBPos.y - oBOrg.y >(pMyBall->spr.getPosition().y)
			&& oBPos.y + oBOrg.y < (pMyBall->spr.getPosition().y))*/
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//{
		//	pMyBall->cDir = true;
		//	return pMyBall->cDir;
		//}
	}
	void Update(sf::RenderWindow& window, float dT)
	{

		// Control
		float SPEED = 350;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if ((spr.getPosition().y + 13) <= spr.getOrigin().y)
				SPEED = 0;		// Stop the bat if it reaches to the top of the screen
			else
				SPEED = SPEED;
			vel = Vec2{ 0, -SPEED };
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if ((spr.getPosition().y - 13) >= (window.getSize().y - spr.getOrigin().y))
				SPEED = 0;		// Stop the bat if it reaches to the bottom of the screen
			else
				SPEED = SPEED;
			vel = Vec2{ 0, SPEED };
		}
		// Simulation
		Vec2 pos{ spr.getPosition() };
		pos += vel * dT;

		spr.setPosition(pos);
		
		Vec2 bPos = pos;
		Vec2 bOrg = spr.getOrigin();

		// Bounce the ball back
		//Bounce(bPos, bOrg);
		/*if (pMyBall)
		{
			pMyBall->ChangeXDirection();
		}*/
	}
	void Render(sf::RenderWindow& window, float dT) override
	{
		Obj2D::Render(window, dT);
	}
};

class Bat2 : public Obj2D
{
public:

	void Init(sf::RenderWindow& window, sf::Texture& tex)
	{
		spr.setTexture(tex, true);
		spr.setTextureRect(sf::IntRect{ 54, 5, 42, 140 });
		spr.setOrigin(21, 70);
		spr.setPosition(window.getSize().x * 0.975f, window.getSize().y * 0.5f);
	}
	void Update(sf::RenderWindow& window, float dT)
	{
		// Control
		float SPEED = 350;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if ((spr.getPosition().y + 13) <= spr.getOrigin().y)
				SPEED = 0;		// Stop the bat if it reaches to the top of the screen
			else
				SPEED = SPEED;
			vel = Vec2{ 0, -SPEED };
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if ((spr.getPosition().y - 13) >= (window.getSize().y - spr.getOrigin().y))
				SPEED = 0;		// Stop the bat if it reaches to the bottom of the screen
			else
				SPEED = SPEED;
			vel = Vec2{ 0, SPEED };
		}

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

//****************************************************************************
int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Ass02_Pong");

	sf::Texture texPong;
	if (!texPong.loadFromFile("data/pongSprites.png"))
		assert(false);
	// Ball
	Ball ball;
	ball.Init(window, texPong);

	// Players
	Bat1 bat1;
	bat1.Init(window, texPong);
	Bat2 bat2;
	bat2.Init(window, texPong);


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

		// Bounce 
		//ball.ChangeXDirection(bat1.spr.getPosition().x);
		//ball.ChangeXDirection(bat2.spr.getPosition().x);

		// Updates
		ball.Update(window, elapsedTime);
		bat1.Update(window, elapsedTime);
		bat2.Update(window, elapsedTime);
		
		window.clear();
		
		// Renders
		ball.Render(window, elapsedTime);
		bat1.Render(window, elapsedTime);
		bat2.Render(window, elapsedTime);

		window.display();
	}
	return EXIT_SUCCESS;
}