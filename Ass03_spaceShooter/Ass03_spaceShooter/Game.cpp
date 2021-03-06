#include "Game.h"
#include "WindowUtils.h"
#include "CommonStates.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

MouseAndKeys Game::sMKIn;
Gamepads Game::sGamepads;

const RECTF missileSpin[]{
	{ 0,  0, 53, 48},
	{ 54, 0, 107, 48 },
	{ 108, 0, 161, 48 },
	{ 162, 0, 220, 48 },
};

const RECTF thrustAnim[]{
	{ 0,  0, 15, 16},
	{ 16, 0, 31, 16 },
	{ 32, 0, 47, 16 },
	{ 48, 0, 64, 16 },
};

Game::Game(MyD3D& d3d)
	: mPMode(d3d), mD3D(d3d), mpSB(nullptr)
	//: mIntro(d3d), mMenu(d3d), mPMode(d3d), mGameOver(d3d), mD3D(d3d), mpSB(nullptr)
{
	sMKIn.Initialise(WinUtil::Get().GetMainWnd(), true, false);
	sGamepads.Initialise();
	mpSB = new SpriteBatch(&mD3D.GetDeviceCtx());
}


//any memory or resources we made need releasing at the end
void Game::Release()
{
	delete mpSB;
	mpSB = nullptr;
}

//called over and over, use it to update game logic
void Game::Update(float dTime)
{
	sGamepads.Update();
	switch (state)
	{
	//case State::INTRO:
	//	mIntro.Update(dTime);
	//case State::M_MENU:
	//	mMenu.Update(dTime);
	case State::PLAY:
		mPMode.Update(dTime);
	//case State::G_OVER:
	//	mGameOver.Update(dTime);
	}
}

//called over and over, use it to render things
void Game::Render(float dTime)
{
	mD3D.BeginRender(Colours::Black);


	CommonStates dxstate(&mD3D.GetDevice());
	mpSB->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &mD3D.GetWrapSampler());

	switch (state)
	{
	//case State::INTRO:
	//	mIntro.Render(dTime, *mpSB);
	//	break;
	//case State::M_MENU:
	//	mMenu.Render(dTime, *mpSB);
	//	break;
	case State::PLAY:
		mPMode.Render(dTime, *mpSB);
		break;
	//case State::G_OVER:
	//	mGameOver.Render(dTime, *mpSB);
	//	break;
	}

	mpSB->End();


	mD3D.EndRender();
	sMKIn.PostProcess();
}

void Bullet::Init(MyD3D& d3d)
{
	vector<RECTF> frames2(missileSpin, missileSpin + sizeof(missileSpin) / sizeof(missileSpin[0]));
	ID3D11ShaderResourceView* p = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "missile.dds", "missile", true, &frames2);

	bullet.SetTex(*p);
	bullet.GetAnim().Init(0, 3, 15, true);
	bullet.GetAnim().Play(true);
	bullet.SetScale(Vector2(0.5f, 0.5f));
	bullet.origin = Vector2((missileSpin[0].right - missileSpin[0].left) / 2.f, (missileSpin[0].bottom - missileSpin[0].top) / 2.f);
	active = false;
}

void Bullet::Render(SpriteBatch& batch)
{
	if (active)
		bullet.Draw(batch);
}

void Bullet::Update(float dTime)
{
	if (active)
	{
		bullet.mPos.x += MISSILE_SPEED * dTime;
		if (bullet.mPos.x > WinUtil::Get().GetClientWidth())
			active = false;
		bullet.GetAnim().Update(dTime);
	}
}

PlayMode::PlayMode(MyD3D & d3d)
	:mD3D(d3d), mPlayer(d3d), mThrust(d3d), mMissile(d3d)
{
	InitBgnd();
	InitPlayer();
}

void PlayMode::UpdateMissile(float dTime)
{
	if (!mMissile.active && (Game::sMKIn.IsPressed(VK_SPACE) ||
		(Game::sGamepads.IsConnected(0) && Game::sGamepads.IsPressed(0, XINPUT_GAMEPAD_A))))
	{
		mMissile.active = true;
		mMissile.bullet.mPos = Vector2(mPlayer.mPos.x + mPlayer.GetScreenSize().x / 2.f, mPlayer.mPos.y);
	}
	mMissile.Update(dTime);
}

void PlayMode::UpdateBgnd(float dTime)
{
	//scroll the background layers
	int i = 0;
	for (auto& s : mBgnd)
		s.Scroll(dTime*(i++)*SCROLL_SPEED, 0);
}

void PlayMode::UpdateInput(float dTime)
{
	Vector2 mouse{ Game::sMKIn.GetMousePos(false) };
	bool keypressed = Game::sMKIn.IsPressed(VK_UP) || Game::sMKIn.IsPressed(VK_DOWN) ||
		Game::sMKIn.IsPressed(VK_RIGHT) || Game::sMKIn.IsPressed(VK_LEFT);
	bool sticked = false;
	if (Game::sGamepads.IsConnected(0) &&
		(Game::sGamepads.GetState(0).leftStickX != 0 || Game::sGamepads.GetState(0).leftStickX != 0))
		sticked = true;

	if (keypressed || (mouse.Length() >VERY_SMALL) || sticked)
	{
		//move the ship around
		Vector2 pos(0, 0);
		if (Game::sMKIn.IsPressed(VK_UP))
			pos.y -= SPEED * dTime;
		else if (Game::sMKIn.IsPressed(VK_DOWN))
			pos.y += SPEED * dTime;
		if (Game::sMKIn.IsPressed(VK_RIGHT))
			pos.x += SPEED * dTime;
		else if (Game::sMKIn.IsPressed(VK_LEFT))
			pos.x -= SPEED * dTime;

		pos += mouse * MOUSE_SPEED * dTime;

		if (sticked)
		{
			DBOUT("left stick x=" << Game::sGamepads.GetState(0).leftStickX << " y=" << Game::sGamepads.GetState(0).leftStickY);
			pos.x += Game::sGamepads.GetState(0).leftStickX * PAD_SPEED * dTime;
			pos.y -= Game::sGamepads.GetState(0).leftStickY * PAD_SPEED * dTime;
		}

		//keep it within the play area
		pos += mPlayer.mPos;
		if (pos.x < mPlayArea.left)
			pos.x = mPlayArea.left;
		else if (pos.x > mPlayArea.right)
			pos.x = mPlayArea.right;
		if (pos.y < mPlayArea.top)
			pos.y = mPlayArea.top;
		else if (pos.y > mPlayArea.bottom)
			pos.y = mPlayArea.bottom;

		mPlayer.mPos = pos;
		mThrusting = GetClock() + 0.2f;
	}
}

void PlayMode::UpdateThrust(float dTime)
{
	if (mThrusting)
	{
		mThrust.mPos = mPlayer.mPos;
		mThrust.mPos.x -= 25;
		mThrust.mPos.y -= 12;
		mThrust.SetScale(Vector2(1.5f, 1.5f));
		mThrust.GetAnim().Update(dTime);
	}
}

void PlayMode::Update(float dTime)
{
	UpdateBgnd(dTime);

	UpdateMissile(dTime);

	UpdateInput(dTime);

	UpdateThrust(dTime);

}

void PlayMode::Render(float dTime, DirectX::SpriteBatch & batch) {
	for (auto& s : mBgnd)
		s.Draw(batch);
	if(mThrusting>GetClock())
		mThrust.Draw(batch);
	mMissile.Render(batch);
	mPlayer.Draw(batch);
}

void PlayMode::InitBgnd()
{
	//a sprite for each layer
	assert(mBgnd.empty());
	mBgnd.insert(mBgnd.begin(), BGND_LAYERS, Sprite(mD3D));

	//a neat way to package pairs of things (nicknames and filenames)
	pair<string, string> files[BGND_LAYERS]{
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
		ID3D11ShaderResourceView *p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), f.second, f.first);
		if (!p)
			assert(false);
		mBgnd[i++].SetTex(*p);
	}
}

void PlayMode::InitPlayer()
{
	//load a orientate the ship
	ID3D11ShaderResourceView *p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), "ship.dds");
	mPlayer.SetTex(*p);
	mPlayer.SetScale(Vector2(0.1f, 0.1f));
	mPlayer.origin = mPlayer.GetTexData().dim / 2.f;
	mPlayer.rotation = PI / 2.f;

	//setup the play area
	int w, h;
	WinUtil::Get().GetClientExtents(w, h);
	mPlayArea.left = mPlayer.GetScreenSize().x*0.6f;
	mPlayArea.top = mPlayer.GetScreenSize().y * 0.6f;
	mPlayArea.right = w - mPlayArea.left;
	mPlayArea.bottom = h * 0.75f;
	mPlayer.mPos = Vector2(mPlayArea.left + mPlayer.GetScreenSize().x / 2.f, (mPlayArea.bottom - mPlayArea.top) / 2.f);

	vector<RECTF> frames(thrustAnim, thrustAnim + sizeof(thrustAnim) / sizeof(thrustAnim[0]));
	p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), "thrust.dds", "thrust", true, &frames);
	mThrust.SetTex(*p);
	mThrust.GetAnim().Init(0, 3, 15, true);
	mThrust.GetAnim().Play(true);
	mThrust.rotation = PI / 2.f;

	mMissile.Init(mD3D);
}