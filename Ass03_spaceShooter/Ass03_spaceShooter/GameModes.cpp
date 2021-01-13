//#include <vector>
//#include "GameModes.h"
//#include "Game.h"
//#include "WindowUtils.h"
//#include "CommonStates.h"
//
//using namespace std;
//using namespace DirectX;
//using namespace DirectX::SimpleMath;
//
//IntroMode::IntroMode(MyD3D& d3d)
//	: mD3D(d3d)
//{
//	InitBgnd();
//}
//
//void IntroMode::InitBgnd()
//{
//	ID3D11ShaderResourceView* p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), MOUNTAINS_BACKGROUND_FILEPATH);
//	mBgndMnt.SetTex(*p);
//	Vector2 scaleBgnd = Vector2(SCREEN_WIDTH / mBgndMnt.GetTexData().dim.x, SCREEN_HEIGHT / mBgndMnt.GetTexData().dim.y);
//	mBgndMnt.SetScale(scaleBgnd);
//	mBgndMnt.origin = mBgndMnt.GetTexData().dim / 2.f;
//}
//
//void IntroMode::Update(float dTime)
//{
//	//if (_clock.getElapsedTime().asSeconds() > INTRO_SHOW_TIME)
//	if (Game::sGamepads.IsConnected(0) && Game::sGamepads.IsPressed(0, XINPUT_GAMEPAD_START))
//	{
//		Game game;
//		state = State::INTRO;
//	}
//}
//
//void IntroMode::Render(float dTime, DirectX::SpriteBatch& batch)
//{
//	mBgndMnt.Draw(batch);
//}
///*
//void PlayMode::InitPlayer()
//{
//	//load a orientate the ship
//	ID3D11ShaderResourceView* p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), "ship.dds");
//	mPlayer.SetTex(*p);
//	mPlayer.SetScale(Vector2(0.1f, 0.1f));
//	mPlayer.origin = mPlayer.GetTexData().dim / 2.f;
//	mPlayer.rotation = PI / 2.f;
//
//	//setup the play area
//	int w, h;
//	WinUtil::Get().GetClientExtents(w, h);
//	mPlayArea.left = mPlayer.GetScreenSize().x * 0.6f;
//	mPlayArea.top = mPlayer.GetScreenSize().y * 0.6f;
//	mPlayArea.right = w - mPlayArea.left;
//	mPlayArea.bottom = h * 0.75f;
//	mPlayer.mPos = Vector2(mPlayArea.left + mPlayer.GetScreenSize().x / 2.f, (mPlayArea.bottom - mPlayArea.top) / 2.f);
//
//	vector<RECTF> frames(thrustAnim, thrustAnim + sizeof(thrustAnim) / sizeof(thrustAnim[0]));
//	p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), "thrust.dds", "thrust", true, &frames);
//	mThrust.SetTex(*p);
//	mThrust.GetAnim().Init(0, 3, 15, true);
//	mThrust.GetAnim().Play(true);
//	mThrust.rotation = PI / 2.f;
//
//	mMissile.Init(mD3D);
//}
//
///*
//void IntroMode::InitBgnd()
//{
//	//a sprite for each layer
//	assert(mBgnd.empty());
//	mBgnd.insert(mBgnd.begin(), BGND_LAYERS, Sprite(mD3D));
//
//	//a neat way to package pairs of things (nicknames and filenames)
//	pair<string, string> files[BGND_LAYERS]{
//		{ "bgnd0","backgroundlayers/mountains01_007.dds" },
//		{ "bgnd1","backgroundlayers/mountains01_005.dds" },
//		{ "bgnd2","backgroundlayers/mountains01_004.dds" },
//		{ "bgnd3","backgroundlayers/mountains01_003.dds" },
//		{ "bgnd4","backgroundlayers/mountains01_002.dds" },
//		{ "bgnd5","backgroundlayers/mountains01_001.dds" },
//		{ "bgnd6","backgroundlayers/mountains01_000.dds" },
//		{ "bgnd7","backgroundlayers/mountains01_006.dds" }
//	};
//	int i = 0;
//	for (auto& f : files)
//	{
//		//set each texture layer
//		ID3D11ShaderResourceView* p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), f.second, f.first);
//		if (!p)
//			assert(false);
//		mBgnd[i++].SetTex(*p);
//	}
//}*/