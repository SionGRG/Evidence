#include "Game.h"
#include <stdlib.h>
#include <ctime>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

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
	
	void Game::Score(sf::RenderWindow& window, sf::Font font)
	{
		sf::Text txtScore;					// score text											
		sf::Text txtP1Score;				// Player 1 score text
		sf::Text txtP2Score;				// Player 2 score text
		
		float scorePos = 40;				// half distance between player 1 and player 2 

		/* score text */
		txtScore.setFont(font);												// select the font
		txtScore.setString("SCORE");										// set the string to display
		txtScore.setCharacterSize(48);										// set the character size		
		txtScore.setFillColor(sf::Color::White);							// set the color
		txtScore.setStyle(sf::Text::Bold);									// set the text style
		// center score text
		sf::FloatRect scoreTxtRect = txtScore.getLocalBounds();
		txtScore.setOrigin(scoreTxtRect.left + scoreTxtRect.width / 2.0f,
			scoreTxtRect.top + scoreTxtRect.height / 2.0f);					// set score origin to the center of the score text
		txtScore.setPosition(window.getSize().x/2,
			window.getSize().y * .025f);									// set the position
		
		/* Player 1 score */
		txtP1Score.setFont(font);											// select the font
		txtP1Score.setString(to_string(p1Score));							// set the string to display
		txtP1Score.setCharacterSize(72);									// set the character size		
		txtP1Score.setFillColor(sf::Color::Red);							// set the color
		txtP1Score.setStyle(sf::Text::Bold);								// set the text style
		// center score text
		sf::FloatRect p1TxtRect = txtP1Score.getLocalBounds();
		txtP1Score.setOrigin(p1TxtRect.left + p1TxtRect.width / 2.0f,
			p1TxtRect.top + p1TxtRect.height / 2.0f);						// set score origin to the center of the score text
		txtP1Score.setPosition((window.getSize().x / 2) - scorePos,
			window.getSize().y * .1f);										// set the position
		
		/* Player 2 score */
		txtP2Score.setFont(font);											// select the font
		txtP2Score.setString(to_string(p2Score));							// set the string to display
		txtP2Score.setCharacterSize(72);									// set the character size		
		txtP2Score.setFillColor(sf::Color::Blue);							// set the color
		txtP2Score.setStyle(sf::Text::Bold);								// set the text style
		// center score text
		sf::FloatRect p2TxtRect = txtP2Score.getLocalBounds();
		txtP2Score.setOrigin(p2TxtRect.left + p2TxtRect.width / 2.0f,
			p2TxtRect.top + p2TxtRect.height / 2.0f);						// set score origin to the center of the score text
		txtP2Score.setPosition((window.getSize().x / 2) + scorePos,
			window.getSize().y * .1f);										// set the position

		// Draw texts
		window.draw(txtScore);
		window.draw(txtP1Score);
		window.draw(txtP2Score);
	}

	void Game::Record(sf::RenderWindow& window)
	{
		// Record player score and reset the ball position goes the beyond the player's bat
		if (ball.spr.getPosition().x < (window.getSize().x * 0) + ball.spr.getOrigin().x)
		{
			++p2Score;
			ball.Reset(window);
		}
		if ((ball.spr.getPosition().x + ball.spr.getOrigin().x) > window.getSize().x)
		{
			++p1Score;
			ball.Reset(window);
		}
		if (p1Score == maxScore || p2Score == maxScore)
		{
			p1Score = 0;
			p2Score = 0;
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

	void Game::Update(sf::RenderWindow& window, float dT, sf::Font font)
	{
		controls();
		// Updates
		ball.Update(window, dT);
		bat1.Update(window, dT);
		bat2.Update(window, dT);

		// Bounce the ball back
		Bounce(bat1, bat2);
		// Record player score and Reset score if it reaches max score
		Record(window);
	}
	
	void Game::Render(sf::RenderWindow& window, float dT, sf::Font font)
	{
		// Object Renders
		ball.Render(window, dT);
		bat1.Render(window, dT);
		bat2.Render(window, dT);
		
		// Score
		Score(window, font);
	}

	void Game::RunGame()
	{
		sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ass02_Pong");
		
		Game game;

		sf::Texture texPong;
		if (!texPong.loadFromFile("data/pongSprites.png"))
			assert(false);
		sf::Font fontPong;
		if (!fontPong.loadFromFile("data/Airstream.ttf"))
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
			game.Update(window, elapsedTime, fontPong);
			window.clear();

			// Renders
			game.Render(window, elapsedTime, fontPong);

			window.display();
		}
	}