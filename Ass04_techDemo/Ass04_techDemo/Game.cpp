#include "Game.h"
#include "WindowUtils.h"
#include "CommonStates.h"
#include "PlayMode.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;




Game::Game(MyD3D& d3d)
	: mD3D(d3d), mpSB(nullptr)
{
	mMKIn.Initialise(WinUtil::Get().GetMainWnd(), true, false);
	mGamepads.Initialise();
	mpSB = new SpriteBatch(&mD3D.GetDeviceCtx());
	mMMgr.AddMode(new PlayMode());
	mMMgr.AddMode(new IntroMode());
	mMMgr.AddMode(new GameOverMode());
	mMMgr.SwitchMode(IntroMode::MODE_NAME);
}


//any memory or resources we made need releasing at the end
void Game::Release()
{
	delete mpSB;
	mpSB = nullptr;
	mMMgr.Release();
}

//called over and over, use it to update game logic
void Game::Update(float dTime)
{
	mGamepads.Update();
	mMMgr.Update(dTime);
}

//called over and over, use it to render things
void Game::Render(float dTime)
{
	mD3D.BeginRender(Colours::Black);


	CommonStates dxstate(&mD3D.GetDevice());
	mpSB->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &mD3D.GetWrapSampler());
	mMMgr.Render(dTime, *mpSB);
	mpSB->End();


	mD3D.EndRender();
	mMKIn.PostProcess();
}


//****************************************************************



//********************************************************************
const std::string IntroMode::MODE_NAME = "INTRO";

IntroMode::IntroMode()
	: mSpr(Game::Get().GetD3D())
{
	mSpr.SetTex(*Game::Get().GetD3D().GetCache().LoadTexture(&Game::Get().GetD3D().GetDevice(), "start1.dds", "start1"));
	mSpr.SetScale(Vector2(WinUtil::Get().GetClientWidth() / mSpr.GetTexData().dim.x, WinUtil::Get().GetClientHeight() / mSpr.GetTexData().dim.y));
}
void IntroMode::Update(float dTime)
{
	if (Game::Get().mGamepads.IsConnected(0) && Game::Get().mGamepads.IsPressed(0, XINPUT_GAMEPAD_START))
	{
		Game::Get().GetModeMgr().SwitchMode(PlayMode::MODE_NAME);
	}
}

void IntroMode::Render(float dTime, DirectX::SpriteBatch& batch)
{
	mSpr.Draw(batch);
}

void IntroMode::ProcessKey(char key)
{
	switch (key)
	{
	case GC::SPACE:
		Game::Get().GetModeMgr().SwitchMode(PlayMode::MODE_NAME);
		break;
	case GC::ESC:
		PostQuitMessage(0);
		break;
	}
}
//********************************************************************
const std::string GameOverMode::MODE_NAME = "GAMEOVER";

GameOverMode::GameOverMode()
	: mSpr(Game::Get().GetD3D())
{
	mSpr.SetTex(*Game::Get().GetD3D().GetCache().LoadTexture(&Game::Get().GetD3D().GetDevice(), "game_over.dds", "gameover"));
	float xscale = (WinUtil::Get().GetClientWidth() * 0.8f) / mSpr.GetTexData().dim.x;
	mSpr.SetScale(Vector2( xscale, xscale));
}
void GameOverMode::Update(float dTime)
{

}

void GameOverMode::Render(float dTime, DirectX::SpriteBatch& batch)
{
	mSpr.Draw(batch);
}

void GameOverMode::ProcessKey(char key)
{
	switch (key)
	{
	case GC::SPACE:
		Game::Get().GetModeMgr().SwitchMode(IntroMode::MODE_NAME);
		break;
	case GC::ESC:
		PostQuitMessage(0);
		break;
	}
}
