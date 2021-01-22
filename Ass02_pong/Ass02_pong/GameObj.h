#pragma once

#include "Definitions.h"
#include "Obj2D.h"

namespace Ass02_pong
{
	class Ball :public Obj2D
	{
	private:
		GameDataRef _data;
	public:
		Ball() {}
		Ball(GameDataRef data);
		~Ball() {}

		float xVel, yVel;
		float SPEED = BALL_SPEED;
		float xDir = 1;
		float yDir = 1;

		int GetRandomNumber(int high, int low)
		{
			return (rand() % high) + low;
		}
		void Init(sf::Texture& tex, int ballTexPosX, int ballTexPosY, int ballTexWidth, int ballTexHeight, float ballPosX, float ballPosY) override;
		void Reset();
		void ChangeXDirection();
		float ChangeYDirection(float& cDirY);
		void Movement(float dT) override;
		void Update(float dT) override;
		void Render(float dT) override;
	};

	class Bat :public Obj2D
	{
	private:
		GameDataRef _data;
	public:
		Bat() {}
		Bat(GameDataRef data);
		~Bat() {}
		// Controls
		sf::Keyboard::Key moveUp;
		sf::Keyboard::Key moveDown;

		void Init(sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY);
		void Movement(float dT) override;
		void Update(float dT) override;
		void Render(float dT) override;
	};

}

