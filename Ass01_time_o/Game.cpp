#include <assert.h>

#include "Game.h"


/*
* Get a random nubmer in the given range
min - IN bottom of the range
max - IN top o fthe range
precond - the random number generator has been seeded
postcond - returns the random result
*/
float GetRandRange(float min, float max)
{
	float toOne = (float)(rand() % RAND_MAX) / (float)RAND_MAX;

	return min + max * toOne;
}
//same thing but pass by reference
void GetRandRange(float min, float max, float& result)
{
	float toOne = (float)(rand() % RAND_MAX) / (float)RAND_MAX;

	result = min + max * toOne;
}


void Game::Keyboard(sf::Keyboard::Key code)
{
	if (code == sf::Keyboard::Space)
	{
		//keyboard stuff
		rndOffset = (float)(rand() % 360);
		rndOffset2 = (float)(rand() % 360);
	}
}


void Game::Initialise()
{
	if (texAnaFace.loadFromFile("data/clock_face.png") == false)
		assert(false);

	if (texAnaHands.loadFromFile("data/clock_hands.png") == false)
		assert(false);

}

void Game::Render(sf::RenderWindow& window)
{
	sf::Vector2f pos{ 600.f,400.f };
	for (int i = 0; i < 20; ++i)
	{
		sf::Vector2f npos;
		float clockAngOff = clockAng + i * 3.141f * 0.1f;
		npos.x = pos.x + sinf(clockAngOff) * 200;
		npos.y = pos.y + cosf(clockAngOff) * 200;
		RenderClockFace(window, npos, baseRotation, 0.25f);
	}
}

void Game::RenderClockFace(sf::RenderWindow& window, sf::Vector2f& pos, float angle, float scale)
{
	sf::Sprite spr(texAnaFace);
	spr.setOrigin(sf::Vector2f{ 256,256 });
	spr.setPosition(pos);
	spr.setScale(scale, scale);
	window.draw(spr);

	spr.setTexture(texAnaHands, true);
	spr.setRotation(angle);
	sf::IntRect rect{ 92,0,60,512 };
	sf::Vector2f ori{ 30,457 };
	spr.setOrigin(ori);
	spr.setPosition(pos);
	spr.setTextureRect(rect);
	spr.setScale(scale * 0.5f, scale * 0.5f);
	window.draw(spr);
}

void Game::Update(float dT)
{
	const float ROT_SPEED = 25;
	baseRotation += dT * ROT_SPEED;
	const float scale = 0.5f;
	clockAng += dT * 0.5f;
}
