#include "Game.h"
#include <stdlib.h>
#include <ctime>

//Ball	*****************************************************************

	void Ball::Init(sf::RenderWindow& window, sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY)
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
	
	void Ball::Reset(sf::RenderWindow& window)
	{
		spr.setPosition(window.getSize().x * 0.5f, window.getSize().y * 0.5f);
		ChangeXDirection();
	}
	
	void Ball::ChangeXDirection()
	{
		xDir *= -1;		// Change the direction of the ball in the x direction
	}
	float Ball::ChangeYDirection(sf::RenderWindow& window, float& cDirY)
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
	
	void Ball::Movement(sf::RenderWindow& window, float dT)
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
	
	void Ball::Update(sf::RenderWindow& window, float dT)
	{
		Movement(window, dT);
	}
	void Ball::Render(sf::RenderWindow& window, float dT)
	{
		Obj2D::Render(window, dT);
		// Fire trails
		// Sparkles
	}
	
//Bat	*****************************************************************
	
	void Bat::Init(sf::RenderWindow& window, sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY)
	{
		spr.setTexture(tex, true);
		//Hint: example: spr.setTextureRect(sf::IntRect{ 4, 5, 42, 140 });
		spr.setTextureRect(sf::IntRect{ batTexPosX, batTexPosY, batTexWidth, batTexHeight });
		//Hint: example: spr.setOrigin(21, 70);
		float batOrgX = batTexWidth / 2;					// set origin().x to the center of the texture
		float batOrgY = batTexHeight / 2;					// set origin().y to the center of the texture
		spr.setOrigin(batOrgX, batOrgY);
		//Hint: example: spr.setPosition(window.getSize().x * 0.05f, window.getSize().y * 0.5f);
		spr.setPosition(window.getSize().x * batPosX, window.getSize().y * batPosY);
	}
	
	void Bat::Movement(sf::RenderWindow& window, float dT)
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
	void Bat::Update(sf::RenderWindow& window, float dT)
	{
		Movement(window, dT);
		// Simulation
		Vec2 pos{ spr.getPosition() };
		pos += vel * dT;
	
		spr.setPosition(pos);
	
	}
	void Bat::Render(sf::RenderWindow& window, float dT)
	{
		Obj2D::Render(window, dT);
	}
	
//Game	*****************************************************************
	
	void Game::Init(sf::RenderWindow& window, sf::Texture& tex)
	{
	
		// Ball
		ball.Init(window, tex, 105, 5, 40, 40, 0.5f, 0.5f);
	
		// Players
		bat1.Init(window, tex, 4, 5, 42, 140, 0.05f, 0.5f);
		bat2.Init(window, tex, 54, 5, 42, 140, 0.95f, 0.5f);
	}
	
	void Game::Score(sf::RenderWindow& window, float dT)
	{
	
	}

	void Game::Record(sf::RenderWindow& window, float dT)
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
	
	void Game::controls()
	{
		// set the player controls
		//player 1
		bat1.moveUp = sf::Keyboard::W;
		bat1.moveDown = sf::Keyboard::S;
		//player 2
		bat2.moveUp = sf::Keyboard::Up;
		bat2.moveDown = sf::Keyboard::Down;
	}
	
	void Game::Bounce(Bat bBat1, Bat bBat2)
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
	
	void Game::Update(sf::RenderWindow& window, float dT)
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
	
	void Game::Render(sf::RenderWindow& window, float dT)
	{
		// Renders
		ball.Render(window, dT);
		bat1.Render(window, dT);
		bat2.Render(window, dT);
	}

	void Game::RunGame()
	{
		sf::RenderWindow window(sf::VideoMode(1366, 768), "Ass02_Pong");
		
		Game game;

		sf::Texture texPong;
		if (!texPong.loadFromFile("data/pongSprites.png"))
			assert(false);

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
	}