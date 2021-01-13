#pragma once

#include <vector>

#include "Input.h"
#include "D3D.h"
#include "SpriteBatch.h"
#include "Sprite.h"

// Parent of all simple 2D objects 
class Obj2D
{
public:
	Sprite spr;
	bool active = false;

	Obj2D(MyD3D& d3d)
		: spr(d3d)
	{}

	virtual ~Obj2D() {}
	virtual void Init(MyD3D& d3d) = 0;
	virtual void Render(DirectX::SpriteBatch& batch) = 0;
	virtual void Update(float dTime) = 0;
};

/*
Animated missile bullet 
Player can only fire one and has to wait for it to leave the 
screen before firing again.
*/
class Bullet : public Obj2D
{
public:
	Bullet(MyD3D& d3d)
		:Obj2D(d3d)
	{}

	void Init(MyD3D& d3d) override {}
	void Render(DirectX::SpriteBatch& batch) override {}
	void Update(float dTime) override {}
	const float MISSILE_SPEED = 300;
};

class Astroid : public Obj2D
{
public:
	Astroid(MyD3D& d3d)
		:Obj2D(d3d)
	{}

	void Init(MyD3D& d3d) override {}
	void Render(DirectX::SpriteBatch& batch) override {}
	void Update(float dTime) override {}
};

/*
class Astroid
{
public:
};

class Astroid
{
public:
};

class Astroid
{
public:
};

class Astroid
{
public:
};

class Astroid
{
public:
};
*/
// class GameOver
// class Settings

class IntroMode
{
public:
	IntroMode(MyD3D& );
	void Update(float dTime);
	void Render(float dTime, DirectX::SpriteBatch& batch);
private: 
	MyD3D mD3D;
	Sprite mBgnd;
};


//horizontal scrolling with player controlled ship
class PlayMode
{
public:
	PlayMode(MyD3D& d3d);
	void Update(float dTime);
	void Render(float dTime, DirectX::SpriteBatch& batch);
private:
	const float SCROLL_SPEED = 10.f;
	static const int BGND_LAYERS = 8;
	const float SPEED = 250;
	const float MOUSE_SPEED = 5000;
	const float PAD_SPEED = 500;

	MyD3D& mD3D;
	std::vector<Sprite> mBgnd; //parallax layers
	Sprite mPlayer;		//jet
	RECTF mPlayArea;	//don't go outside this	
	Sprite mThrust;		//flames out the back
	std::vector<Bullet*> mMissiles;	//weapon, only one at once 
	float mBulletRelTimer = 0;
	
	//once we start thrusting we have to keep doing it for 
	//at least a fraction of a second or it looks whack
	float mThrusting = 0; 

	//setup once
	void InitBgnd();
	void InitPlayer();

	//make it move, reset it once it leaves the screen, only one at once
	void UpdateMissile(float dTime);
	//make it scroll parallax
	void UpdateBgnd(float dTime);
	//move the ship by keyboard, gamepad or mouse
	void UpdateInput(float dTime);
	//make the flames wobble when the ship moves
	void UpdateThrust(float dTime);
};


/*
Basic wrapper for a game
*/
class Game
{
public:
	enum class State { INTRO, PLAY };
	static MouseAndKeys sMKIn;
	static Gamepads sGamepads;
	State state = State::PLAY;
	Game(MyD3D& d3d);


	void Release();
	void Update(float dTime);
	void Render(float dTime);
private:
	MyD3D& mD3D;
	DirectX::SpriteBatch *mpSB = nullptr;
	//not much of a game, but this is it
	PlayMode mPMode;
};


