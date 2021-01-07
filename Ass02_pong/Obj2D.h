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
			float batTexPosX;		set the texture's rectangular x position value
			float batTexPosY;		set the texture's rectangular y position value
			float batTexWidth;		set the texture's rectangular width value
			float batTexHeight;		set the texture's rectangular height value
			float batPosX;			set the sprite's x position relative to the window size ie. a value that will be multiplied with the window size x value (must be between 0.f and 1.f)
			float batPosY;			set the sprite's y position relative to the window size ie. a value that will be multiplied with the window size y value (must be between 0.f and 1.f)
		*/
		virtual void Init(sf::Texture& tex, int batTexPosX, int batTexPosY, int batTexWidth, int batTexHeight, float batPosX, float batPosY) = 0;
		
		virtual void Movement(float dT) = 0;

		virtual void Update(float dT) = 0;
		
		virtual void Render(float dT) = 0
		{
			//_data->window.draw(spr);
		}
	private:
		GameDataRef _data;
	};
}

