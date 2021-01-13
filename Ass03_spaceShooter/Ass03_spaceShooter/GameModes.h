//#pragma once
//#include <vector>
//
//#include "Input.h"
//#include "D3D.h"
//#include "SpriteBatch.h"
//#include "Sprite.h"
//#include "Game.h"
//#include "Definitions.h"
//#include "SimpleMath.h"
///*
//class GameModes
//{
//public:
//	GameModes();
//	~GameModes();
//
//	GameModes(MyD3D& d3d);
//	virtual void Update(float dTime) = 0;
//	virtual void Render(float dTime, DirectX::SpriteBatch& batch) = 0;
//private:
//	const float SCROLL_SPEED = 10.f;
//	static const int BGND_LAYERS = 8;
//	const float SPEED = 250;
//	const float MOUSE_SPEED = 5000;
//	const float PAD_SPEED = 500;
//
//	//setup once
//	virtual void InitBgnd() = 0;
//
//	MyD3D& mD3D;
//	Sprite mBgndMnt;						// Mountains background
//	std::vector<Sprite> mBgnd;				//parallax layers
//};
//*/
//class IntroMode //: public GameModes
//{
//public:
//	IntroMode();
//	~IntroMode();
//
//	IntroMode(MyD3D& d3d);
//	/*virtual */void Update(float dTime);// override;
//	/*virtual */void Render(float dTime, DirectX::SpriteBatch& batch);// override;
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
//	/*virtual */void Update(float dTime);// override;
//	/*virtual */void Render(float dTime, DirectX::SpriteBatch& batch);// override;
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
//	/*virtual */void Update(float dTime);// override;
//	/*virtual */void Render(float dTime, DirectX::SpriteBatch& batch);// override;
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
//class PlayMode
//{
//public:
//	PlayMode(MyD3D& d3d);
//	void Update(float dTime);
//	void Render(float dTime, DirectX::SpriteBatch& batch);
//private:
//	const float SCROLL_SPEED = 10.f;
//	static const int BGND_LAYERS = 8;
//	const float SPEED = 250;
//	const float MOUSE_SPEED = 5000;
//	const float PAD_SPEED = 500;
//
//	MyD3D& mD3D;
//	std::vector<Sprite> mBgnd;				//parallax layers
//	Sprite mPlayer;							//jet
//	RECTF mPlayArea;						//don't go outside this	
//	Sprite mThrust;							//flames out the back
//	Bullet mMissile;						//weapon, only one at once
//
//	//once we start thrusting we have to keep doing it for 
//	//at least a fraction of a second or it looks whack
//	float mThrusting = 0;
//
//	//setup once
//	void InitBgnd();
//	void InitPlayer();
//
//	//make it move, reset it once it leaves the screen, only one at once
//	void UpdateMissile(float dTime);
//	//make it scroll parallax
//	void UpdateBgnd(float dTime);
//	//move the ship by keyboard, gamepad or mouse
//	void UpdateInput(float dTime);
//	//make the flames wobble when the ship moves
//	void UpdateThrust(float dTime);
//};
