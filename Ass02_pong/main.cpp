#include <assert.h>
#include "SFML/Graphics.hpp"

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
public:
	void Render(sf::RenderWindow& window, float dT) override
	{
		Obj2D::Render(window, dT);
		//fire trails
		//Sparkles
	}
	void Update(sf::RenderWindow& window, float dT) override
	{
		//check for hitting walls
	}
	void Init(sf::RenderWindow& window, sf::Texture& tex) 
	{
		spr.setTexture(tex, true);
		spr.setTextureRect(sf::IntRect{ 92, 0, 56, 56 });
		spr.setOrigin(28, 28);
		spr.setPosition(window.getSize().x * 0.5f, window.getSize().y * 0.9f);
	}
};

class Bat1 : public Obj2D
{
public:

	Ball* pMyBall = nullptr;


	void Init(sf::RenderWindow& window, sf::Texture& tex, Ball& ball)
	{
		pMyBall = &ball;
		Init(window, tex);
	}

	void Init(sf::RenderWindow& window, sf::Texture& tex)
	{
		spr.setTexture(tex, true);
		//spr.setTextureRect(sf::IntRect{ 105, 103, 143, 48 });
		spr.setTextureRect(sf::IntRect{ 4, 5, 42, 140 });
		spr.setOrigin(21, 70);
		//spr.setPosition(window.getSize().x * 0.95f, window.getSize().y * 0.5f);
		spr.setPosition(window.getSize().x * 0.025f, window.getSize().y * 0.5f);
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

		if (pMyBall)
		{
			pMyBall->spr.setPosition(spr.getPosition());
		}
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
	sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML works!");

	sf::Texture texPong;
	if (!texPong.loadFromFile("data/pongSprites.png"))
		assert(false);
	// Ball
	Ball ball;
	ball.Init(window, texPong);

	// Players
	Bat1 bat1;
	bat1.Init(window, texPong, ball);
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