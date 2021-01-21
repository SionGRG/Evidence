#include "PlayMode.h"
#include "WindowUtils.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const TexCache::TexData::Sprite missileSpin[]{
	{{0,0}, false, { 0,  0, 53, 48} },
	{{0,0}, false, { 54, 0, 107, 48} },
	{{0,0}, false, { 108, 0, 161, 48}},
	{{0,0}, false, { 162, 0, 220, 48} },
};

const TexCache::TexData::Sprite thrustAnim[]{
	{{0,0}, false, { 0,  0, 15, 16} },
	{{0,0}, false, { 16, 0, 31, 16} },
	{{0,0}, false, { 32, 0, 47, 16} },
	{{0,0}, false, { 48, 0, 64, 16} },
};

Bullet::Bullet(MyD3D & d3d)
	:GameObj(d3d)
{
	vector<TexCache::TexData::Sprite> frames2(missileSpin, missileSpin + sizeof(missileSpin) / sizeof(missileSpin[0]));
	ID3D11ShaderResourceView* p = d3d.GetCache().LoadTexture(&d3d.GetDevice(), MISSILE_TEXTURE, "missile", true, &frames2);

	mSpr.SetTex(*p);
	mSpr.GetAnim().Init(0, 3, 15, true);
	mSpr.GetAnim().Play(true);
	mSpr.SetScale(Vector2((SCREEN_WIDTH / mSpr.GetTexData().dim.x) * 0.1f, 
		(SCREEN_HEIGHT / mSpr.GetTexData().dim.y) * 0.035f));
	mSpr.origin = Vector2((missileSpin[0].dim.right - missileSpin[0].dim.left) / 2.f, (missileSpin[0].dim.bottom - missileSpin[0].dim.top) / 2.f);
	mActive = false;
}

void Bullet::Update(float dTime)
{
	if (mActive)
	{
		mSpr.mPos.x += GC::MISSILE_SPEED * dTime;
		if (mSpr.mPos.x > WinUtil::Get().GetClientWidth())
			mActive = false;
		mSpr.GetAnim().Update(dTime);
	}
}

// Asteroids
const TexCache::TexData::Sprite asteroids[]{
	{{0,0}, false, { 0, 0, 128 , 128 } },
	{{0,0}, false, { 128, 0, 128 , 128 }},
	{{0,0}, false, { 256, 0, 128 , 128 }},
	{{0,0}, false, { 384, 0, 128 , 128 }},
	{{0,0}, false, { 512, 0, 128 , 128 }},
	{{0,0}, false, { 640, 0, 128 , 128 }},
	{{0,0}, false, { 768, 0, 128 , 128 }},
	{{0,0}, false, { 896, 0, 128 , 128 }},
};

Asteroid::Asteroid(MyD3D& d3d)
	: GameObj(d3d),
	mExplosion(d3d)
{
	ID3D11ShaderResourceView* a = d3d.GetCache().LoadTexture(&d3d.GetDevice(), ASTEROID_TEXTURE);

	mSpr.SetTex(*a, asteroids[0].dim);
	mSpr.SetScale(Vector2((SCREEN_WIDTH / mSpr.GetTexData().dim.x) * 0.35f,
		(SCREEN_WIDTH / mSpr.GetTexData().dim.y) * 0.35f));
	mSpr.origin = Vector2((asteroids[0].dim.right - asteroids[0].dim.left) / 2.f, (asteroids[0].dim.bottom - asteroids[0].dim.top) / 2.f);
	mSpr.rotation = PI / 2.f;

	mSpr.mPos = Vector2(SCREEN_WIDTH * .75, SCREEN_HEIGHT * .025f);			// Spawning positions
	mActive = false;
}

void Asteroid::Update(float dTime)
{
	if (mActive)
	{
		mSpr.mPos.x -= mAsteroidSpeed * dTime;
		mSpr.mPos.y += mAsteroidGravityPull * dTime;
		if (mSpr.mPos.x < 0 || mSpr.mPos.x > WinUtil::Get().GetClientWidth() 
			|| mSpr.mPos.y > WinUtil::Get().GetClientHeight())
			mActive = false;
	}
}
// Explosion
//...To be implemented



//****************************************************************

void Player::Update(float dTime)
{
	Game& gm = Game::Get();
	GameObj* pAstrd = mpMyMode->FindFirst(typeid(Asteroid), false);
	GameObj* pM = mpMyMode->FindFirst(typeid(Bullet), false);
	// Spawn astroids
	if(GetClock() > mAsteroidTimer)
	{
		if (pAstrd)
		{
			pAstrd->mActive = true;
			srand((unsigned)time(0));
			float randPos = pAstrd->mSpr.GetScale().x * (rand() % 7);
			pAstrd->mSpr.mPos = Vector2(SCREEN_WIDTH * .75 * randPos, SCREEN_WIDTH * .025 * randPos);
			if (pAstrd->mSpr.mPos.x < SCREEN_WIDTH * .5)
				pAstrd->mSpr.mPos.x += SCREEN_WIDTH * .45;
			mAsteroidTimer = GetClock() + GC::ASTEROID_SPAWN_DELAY;
		}
	}

	if (playerHealth <= 0)
	{
		Game::Get().GetModeMgr().SwitchMode(GameOverMode::MODE_NAME);
	}

	// Shoot Missiles
	if ( (gm.mMKIn.IsPressed(VK_SPACE) || gm.mMKIn.GetMouseButton(MouseAndKeys::ButtonT::LBUTTON) ||
		(gm.mGamepads.IsConnected(0) && gm.mGamepads.IsPressed(0, XINPUT_GAMEPAD_A))) &&
		GetClock() > mFireTimer)
	{
		if (pM) {
			pM->mActive = true;
			pM->mSpr.mPos = Vector2(mSpr.mPos.x + mSpr.GetScreenSize().x / 2.f, mSpr.mPos.y);
			mFireTimer = GetClock() + GC::FIRE_DELAY;
		}
	}

	if (mThrusting)
	{
		mThrust.mPos = mSpr.mPos;
		mThrust.mPos.x -= (SCREEN_WIDTH / 45);
		mThrust.mPos.y -= (SCREEN_HEIGHT / 45);
		mThrust.SetScale(Vector2((SCREEN_WIDTH / mThrust.GetTexData().dim.x) * 0.1f, 
			(SCREEN_HEIGHT / mThrust.GetTexData().dim.y) * 0.1f));
		mThrust.GetAnim().Update(dTime);

	}
	Vector2 mouse{ gm.mMKIn.GetMousePos(false) };
	bool keypressed = gm.mMKIn.IsPressed(VK_UP) || gm.mMKIn.IsPressed(VK_DOWN) ||
		gm.mMKIn.IsPressed(VK_RIGHT) || gm.mMKIn.IsPressed(VK_LEFT);
	bool sticked = false;
	if (gm.mGamepads.IsConnected(0) &&
		(gm.mGamepads.GetState(0).leftStickX != 0 || gm.mGamepads.GetState(0).leftStickX != 0))
		sticked = true;

	if (keypressed || (mouse.Length() > VERY_SMALL) || sticked)
	{
		//move the ship around
		Vector2 pos(0, 0);
		if (gm.mMKIn.IsPressed(VK_UP))
			pos.y -= GC::SPEED * dTime;
		else if (gm.mMKIn.IsPressed(VK_DOWN))
			pos.y += GC::SPEED * dTime;
		if (gm.mMKIn.IsPressed(VK_RIGHT))
			pos.x += GC::SPEED * dTime;
		else if (gm.mMKIn.IsPressed(VK_LEFT))
			pos.x -= GC::SPEED * dTime;

		pos += mouse * GC::MOUSE_SPEED * dTime;

		if (sticked)
		{
			DBOUT("left stick x=" << gm.mGamepads.GetState(0).leftStickX << " y=" << gm.mGamepads.GetState(0).leftStickY);
			pos.x += gm.mGamepads.GetState(0).leftStickX * GC::PAD_SPEED * dTime;
			pos.y -= gm.mGamepads.GetState(0).leftStickY * GC::PAD_SPEED * dTime;
		}

		//keep it within the play area
		pos += mSpr.mPos;
		if (pos.x < mPlayArea.left)
			pos.x = mPlayArea.left;
		else if (pos.x > mPlayArea.right)
			pos.x = mPlayArea.right;
		if (pos.y < mPlayArea.top)
			pos.y = mPlayArea.top;
		else if (pos.y > mPlayArea.bottom)
			pos.y = mPlayArea.bottom;

		mSpr.mPos = pos;
		mThrusting = GetClock() + 0.2f;
	}
}

Player::Player()
	: GameObj(Game::Get().GetD3D()),
	mThrust(Game::Get().GetD3D())
{
	Init();
}

void Player::Init()
{
	MyD3D& d3d = Game::Get().GetD3D();
	//load a orientate the ship
	ID3D11ShaderResourceView *p = d3d.GetCache().LoadTexture(&d3d.GetDevice(), SHIP_TEXTURE);
	mSpr.SetTex(*p);
	mSpr.SetScale(Vector2((SCREEN_WIDTH / mSpr.GetTexData().dim.x) * 0.075f,
		(SCREEN_WIDTH / mSpr.GetTexData().dim.y) * 0.075f));
	mSpr.origin = mSpr.GetTexData().dim / 2.f;
	mSpr.rotation = PI / 2.f;

	//setup the play area
	int w, h;
	WinUtil::Get().GetClientExtents(w, h);
	mPlayArea.left = mSpr.GetScreenSize().x*0.6f;
	mPlayArea.top = mSpr.GetScreenSize().y * 0.6f;
	mPlayArea.right = w - mPlayArea.left;
	mPlayArea.bottom = h * 0.75f;
	mSpr.mPos = Vector2(mPlayArea.left + mSpr.GetScreenSize().x / 2.f, (mPlayArea.bottom - mPlayArea.top) / 2.f);

	vector<TexCache::TexData::Sprite> frames(thrustAnim, thrustAnim + sizeof(thrustAnim) / sizeof(thrustAnim[0]));
	p = d3d.GetCache().LoadTexture(&d3d.GetDevice(), THRUST_TEXTURE, "thrust", true, &frames);
	mThrust.SetTex(*p);
	mThrust.GetAnim().Init(0, 3, 15, true);
	mThrust.GetAnim().Play(true);
	mThrust.rotation = PI / 2.f;
}

void Player::Render(float dTime, SpriteBatch& batch)
{
	if (mThrusting > GetClock())
		mThrust.Draw(batch);
	GameObj::Render(dTime, batch);
}
//********************************************************************
/* PLAY MODE */

const std::string PlayMode::MODE_NAME = "PLAY";

PlayMode::PlayMode()
{
	InitBgnd();
	mObjects.reserve(1000);
	
	player->SetMode(*this);
	player->mActive = true;
	Add(player);
	
	Add(bullet);
	Add(asteroid);
		
}

PlayMode::~PlayMode()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
		delete mObjects[i];
	mObjects.clear();
}

void PlayMode::UpdateBgnd(float dTime)
{
	//scroll the background layers
	int i = 0;
	for (auto& s : mBgnd)
		s.Scroll(dTime*(i++)*GC::SCROLL_SPEED, 0);
}

void PlayMode::Update(float dTime)
{
	UpdateBgnd(dTime);

	for (size_t i = 0; i < mObjects.size(); ++i)
		if (mObjects[i]->mActive)
			mObjects[i]->Update(dTime);	

	// Collisions
	if ((player->mActive && asteroid->mActive && (player->mSpr.mPos.x > asteroid->mSpr.mPos.x) &&
		((player->mSpr.mPos.y > asteroid->mSpr.mPos.y - asteroid->mSpr.origin.y) &&
		(player->mSpr.mPos.y < asteroid->mSpr.mPos.y + asteroid->mSpr.origin.y))))
	{
		asteroid->mActive = false;
		//player->playerHealth--;
		Game::Get().GetModeMgr().SwitchMode(GameOverMode::MODE_NAME);
	}

	if ((bullet->mActive && asteroid->mActive && (bullet->mSpr.mPos.x > asteroid->mSpr.mPos.x) &&
		((bullet->mSpr.mPos.y > asteroid->mSpr.mPos.y - asteroid->mSpr.origin.y) &&
		 (bullet->mSpr.mPos.y < asteroid->mSpr.mPos.y + asteroid->mSpr.origin.y))))
	{
		player->playerScore += 10;
		bullet->mActive = false;
		asteroid->mActive = false;
		RecordScore = player->playerScore;
	}
}


void PlayMode::Render(float dTime, DirectX::SpriteBatch & batch) {
	for (auto& s : mBgnd)
		s.Draw(batch);
	for (size_t i = 0; i < mObjects.size(); ++i)
		if (mObjects[i]->mActive)
			mObjects[i]->Render(dTime, batch);
}

void PlayMode::InitBgnd()
{
	//a sprite for each layer
	assert(mBgnd.empty());
	mBgnd.insert(mBgnd.begin(), GC::BGND_LAYERS, Sprite(Game::Get().GetD3D()));

	//a neat way to package pairs of things (nicknames and filenames)
	pair<string, string> files[GC::BGND_LAYERS]{
		{ "bgnd0","backgroundlayers/mountains01_007.dds" },
		{ "bgnd1","backgroundlayers/mountains01_005.dds" },
		{ "bgnd2","backgroundlayers/mountains01_004.dds" },
		{ "bgnd3","backgroundlayers/mountains01_003.dds" },
		{ "bgnd4","backgroundlayers/mountains01_002.dds" },
		{ "bgnd5","backgroundlayers/mountains01_001.dds" },
		{ "bgnd6","backgroundlayers/mountains01_000.dds" },
		{ "bgnd7","backgroundlayers/mountains01_006.dds" }
	};
	int i = 0;
	for (auto& f : files)
	{
		//set each texture layer
		ID3D11ShaderResourceView *p = Game::Get().GetD3D().GetCache().LoadTexture(&Game::Get().GetD3D().GetDevice(), f.second, f.first);
		if (!p)
			assert(false);
		mBgnd[i++].SetTex(*p);
	}
	// Scale the background with the screen size
	for (int i = 0; i < mBgnd.size(); i++)
	{
		mBgnd[i].SetScale(Vector2(SCREEN_WIDTH / mBgnd[i].GetTexData().dim.x, 
			SCREEN_HEIGHT / mBgnd[i].GetTexData().dim.y));
	}
}

void PlayMode::ProcessKey(char key)
{
	switch (key)
	{
	case GC::ESC:
		Game::Get().GetModeMgr().SwitchMode(GameOverMode::MODE_NAME);
		break;
	}
}

void PlayMode::Add(GameObj* pObj) {
	assert(pObj);
	mObjects.push_back(pObj);
}

void PlayMode::Remove(GameObj* pObj) {
	size_t sz = mObjects.size();
	assert(sz > 0);
	mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), pObj));
	assert(sz != mObjects.size());
	delete pObj;
}

GameObj* PlayMode::FindFirst(const std::type_info& type, bool active) {
	size_t i = 0;
	while (i < mObjects.size() && (typeid(*mObjects[i]) != type || mObjects[i]->mActive != active))
		++i;
	if (i >= mObjects.size())
		return nullptr;
	return mObjects[i];
}
