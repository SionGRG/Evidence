#pragma once

#include <vector>

#include "Input.h"
#include "D3D.h"
#include "SpriteBatch.h"
#include "Sprite.h"
#include "ModeMgr.h"
#include <iostream>

/*
Animated missile bullet 
Player can only fire one and has to wait for it to leave the 
screen before firing again.
*/
struct Bullet
{
	Bullet(MyD3D& d3d)
		:bullet(d3d)
	{}
	Sprite bullet;
	bool active = false;

	void Init(MyD3D& d3d);
	void Render(DirectX::SpriteBatch& batch);
	void Update(float dTime);
	const float MISSILE_SPEED = 300;
};


///////////////////////////////////////////////////////////////////////////////

//class IntroMode
//{
//public:
//	IntroMode(MyD3D& d3d);
//	void Update(float dTime);
//	void Render(float dTime, DirectX::SpriteBatch& batch);
//
//private:
//	const float SCROLL_SPEED = 10.f;
//	static const int BGND_LAYERS = 8;
//	//setup once
//	void InitBgnd();
//
//	MyD3D& mD3D;
//	Sprite mBgndMnt;						// Mountains background
//	std::vector<Sprite> mBgnd;				// parallax layers
//};
//
//class MainMenuMode //: public GameModes
//{
//public:
//	MainMenuMode();
//	~MainMenuMode();
//
//	MainMenuMode(MyD3D& d3d);
//	void Update(float dTime);
//	void Render(float dTime, DirectX::SpriteBatch& batch);
//
//private:
//	//setup once
//	void InitBgnd();// override;
//
//	MyD3D& mD3D;
//	Sprite mBgndMnt;						// Mountains background
//	std::vector<Sprite> mBgnd;				// parallax layers
//
//};
//
//class GameOverMode //: public GameModes
//{
//public:
//	GameOverMode();
//	~GameOverMode();
//
//	GameOverMode(MyD3D& d3d);
//	void Update(float dTime);
//	void Render(float dTime, DirectX::SpriteBatch& batch);
//
//private:
//	//setup once
//	void InitBgnd();
//
//	MyD3D& mD3D;
//	Sprite mBgndMnt;						// Mountains background
//	std::vector<Sprite> mBgnd;				// parallax layers
//};
//
///////////////////////////////////////////////////////////////////////////////

//horizontal scrolling with player controlled ship
class PlayMode
{
public:
	PlayMode();
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
	Bullet mMissile;	//weapon, only one at once
	
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

	enum class State { INTRO, M_MENU, PLAY, G_OVER };
	static MouseAndKeys sMKIn;
	static Gamepads sGamepads;
	//State state = State::INTRO;
	State state = State::PLAY;
	Game(MyD3D& d3d);
	
	void Release();
	void Update(float dTime);
	void Render(float dTime);
private:
	MyD3D& mD3D;
	DirectX::SpriteBatch *mpSB = nullptr;
	/* Game Modes */
	//IntroMode mIntro;
	//MainMenuMode mMenu;
	PlayMode mPMode;
	//GameOverMode mGameOver;
};
