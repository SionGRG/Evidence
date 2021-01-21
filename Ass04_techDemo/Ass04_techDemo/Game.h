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
#include "MenuMgr.h"
#include "Definitions.h"

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
	const float GRAVITY = SCREEN_WIDTH * .0075f;
	const int MAX_ASTEROIDS = 10;
	const float ASTEROID_SPEED = SCREEN_WIDTH * .15;
	const float ASTEROID_SPAWN_DELAY = 0.5f;
	const float PLAYERHEALTH = 300.f;
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
	bool Exit() override;
	void Enter() override;
private:
	Sprite mSpr;
	void HandleUIEvent(MenuNode& node, MenuNode::Event etype);
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
	bool Exit() override;
	void Enter() override;
private:
	Sprite mSpr;
	void HandleUIEvent(MenuNode& node, MenuNode::Event etype);
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
		mModeMgr.ProcessKey(key);
	}
	//getters
	MyD3D& GetD3D() { return mD3D; }
	ModeMgr& GetModeMgr() { return mModeMgr; }
	MenuMgr& GetMenuMgr() { return mMenuMgr; }
private:
	MyD3D& mD3D;	//main access point to D3D
	DirectX::SpriteBatch* mpSB = nullptr;	//for sprite rendering
	ModeMgr mModeMgr;	//different bits of the game: intro, game, gameOver
	MenuMgr mMenuMgr;	//different menu screens

	//create the different menuscreens and setup each tree of nodes
	void ConfigureUI();
};
