#pragma once

#include <vector>
#include <algorithm>
#include <assert.h>

#include "Input.h"
#include "D3D.h"
#include "SpriteBatch.h"
#include "Sprite.h"
#include "Singleton.h"
#include "ModeMgr.h"

namespace GC {
	const int ESC = 27;
	const int SPACE = 32;
	const float SPEED = 250;
	const float MOUSE_SPEED = 5000;
	const float PAD_SPEED = 500;
	const float FIRE_DELAY = 0.25f;
	const float MISSILE_SPEED = 300;
	const float SCROLL_SPEED = 10.f;
	const int BGND_LAYERS = 8;
	const float GRAVITY = 9.8f;
	const int MAX_ASTEROIDS = 10;
	const float ASTEROID_SPEED = 200;
	const float ASTEROID_SPAWN_DELAY = 0.5f;
};

class IntroMode : public AMode
{
public:
	static const std::string MODE_NAME;
	IntroMode();
	void Update(float dTime) override;
	void Render(float dTime, DirectX::SpriteBatch& batch) override;
	std::string GetMName() const override {
		return "INTRO";
	}
	void ProcessKey(char key) override;
private:
	Sprite mSpr;
};

class GameOverMode : public AMode
{
public:
	static const std::string MODE_NAME;
	GameOverMode();
	void Update(float dTime) override;
	void Render(float dTime, DirectX::SpriteBatch& batch) override;
	std::string GetMName() const override {
		return "GAMEOVER";
	}
	void ProcessKey(char key) override;
private:
	Sprite mSpr;
};

/*
Basic wrapper for a game
*/
class Game : public Singleton<Game> 
{
public:
	MouseAndKeys mMKIn;
	Gamepads mGamepads;

	Game(MyD3D& d3d);
	~Game() {
		Release();
	}
	void Release();
	void Update(float dTime);
	void Render(float dTime);
	void ProcessKey(char key) {
		mMMgr.ProcessKey(key);
	}
	MyD3D& GetD3D() { return mD3D; }
	ModeMgr& GetModeMgr() { return mMMgr; }
private:
	MyD3D& mD3D;
	DirectX::SpriteBatch *mpSB = nullptr;
	ModeMgr mMMgr;
};


