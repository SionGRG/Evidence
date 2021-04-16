#pragma once

#include <assert.h>
#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <ctime>
#include "Definitions.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "GameOverState.h"

using namespace std;


namespace Ass02_pong
{
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

		Obj2D() {}
		Obj2D(GameDataRef data);
		virtual ~Obj2D() {}

		/*	Build a texture and set sprite position
			float texPosX;				set the texture's rectangular x position value
			float texPosY;				set the texture's rectangular y position value
			float texWidth;				set the texture's rectangular width value
			float texHeight;			set the texture's rectangular height value
			float sprPosX;				set the sprite's x position relative to the window size ie. a value that will be multiplied with the window size x value (must be between 0.f and 1.f)
			float sprPosY;				set the sprite's y position relative to the window size ie. a value that will be multiplied with the window size y value (must be between 0.f and 1.f)
		*/
		virtual void Init(sf::Texture& tex, int texPosX, int texPosY, int texWidth, int texHeight, float sprPosX, float sprPosY) = 0;
		
		virtual void Update(float dT) = 0;
		
		virtual void Render(float dT) = 0 {}
	private:
		GameDataRef _data;
	};

	class text
	{
	private:
		GameDataRef _data;
	public:
		text() {}
		text(GameDataRef data);
		~text() {}

		void Init(sf::Text txt, sf::Font font);
		void Update(float dT);
		void Render(float dT);
	};
}

