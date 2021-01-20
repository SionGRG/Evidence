#pragma once

#include <vector>

#include "D3D.h"
#include "SpriteBatch.h"
#include "Sprite.h"
#include "Singleton.h"
#include "ModeMgr.h"
#include "GameObj.h"
#include "Definitions.h"



class PlayMode;

/*
Animated missile bullet
It goes to sleep when it leaves the screen
*/
class Bullet : public GameObj
{
public:

	Bullet(MyD3D& d3d);
	void Update(float dTime) override;
};

class Asteroid : public GameObj
{
public:
	Asteroid(MyD3D& d3d);
	void Update(float dTime) override;
	float mSpawnPosX = SCREEN_WIDTH * .75;			// Spawning positions
	int mSpawn = 16;								// Number of Spawns on Screen
	int mSpawns = 0;								// Number of Spawns on Screen
	float mSpawnTimer = 16.f;						// time limit on Spawning
	int mMaxSpawns = 20;						// time limit on Spawning

	// the asteroid needs a link to the mode it belongs to
	void SetMode(PlayMode& pm) {
		maMyMode = &pm;
	}
private:
	Sprite mExplosion;								// Explode when destroyed
	PlayMode* maMyMode = nullptr;					// my mode owner
public:
	void Init(int mSpawn);
};

class Explosion : public GameObj
{
public:

	Explosion(MyD3D& d3d);
	void Update(float dTime) override;
};


/*
The player's ship, flies around the screen, it shows a thrust
anim when in motion and can periodically fire a bullet forwards
*/
class Player : public GameObj
{
public:
	Player();
	void Render(float dTime, DirectX::SpriteBatch& batch) override;
	void Update(float dTime) override;
	//the player needs a link to the mode it belongs to
	void SetMode(PlayMode& pm) {
		mpMyMode = &pm;
	}

private:
	Sprite mThrust;		//flames out the back
	//once we start thrusting we have to keep doing it for 
	//at least a fraction of a second or it looks whack
	float mThrusting = 0;
	RECTF mPlayArea;				//where can I move?
	PlayMode *mpMyMode = nullptr;	//my mode owner
	float mFireTimer = 0;			//time limit on firing

	void Init();
};


//horizontal scrolling with player controlled ship
class PlayMode : public AMode
{
public:
	static const std::string MODE_NAME;
	PlayMode();
	~PlayMode();
	void Update(float dTime) override;
	void Render(float dTime, DirectX::SpriteBatch& batch) override;
	std::string GetMName() const override { return "PLAY"; }
	void ProcessKey(char key) override;
	/*
	add a GameObj to the mObjects array, the object should be indvidually
	dynamically allocated e.g. pmode.Add(new Bullet(d3d));
	*/
	void Add(GameObj* pObj);
	/*
	Remove and delete the specified object from the mObjects array
	*/
	void Remove(GameObj* pObj);
	/*
	Given the type of the object and whether it should be active or inactive
	find the first matching object in the mObjects array
	*/
	GameObj* FindFirst(const std::type_info& type, bool active);

private:

	std::vector<Sprite> mBgnd;						// parallax layers
	std::vector<GameObj*> mObjects;					// objects needing update/render

	//setup once
	void InitBgnd();

	//make it scroll parallax
	void UpdateBgnd(float dTime);

	// update asteroids
	void UpdateAstrd(float dTime);
};
