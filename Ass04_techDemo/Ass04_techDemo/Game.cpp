#include "Game.h"
#include "WindowUtils.h"
#include "CommonStates.h"
#include "PlayMode.h"
#include "UIConfig.h"
#include "MenuMgr.h"
#include "MenuNodes.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;




Game::Game(MyD3D& d3d)
	: mD3D(d3d), mpSB(nullptr)
{
	mMKIn.Initialise(WinUtil::Get().GetMainWnd(), true, false);
	mGamepads.Initialise();
	mpSB = new SpriteBatch(&mD3D.GetDeviceCtx());
	ConfigureUI();
	mModeMgr.AddMode(new PlayMode());
	mModeMgr.AddMode(new IntroMode());
	mModeMgr.AddMode(new GameOverMode());
	mModeMgr.SwitchMode(IntroMode::MODE_NAME);
}


//any memory or resources we made need releasing at the end
void Game::Release()
{
	delete mpSB;
	mpSB = nullptr;
	mModeMgr.Release();
}

//called over and over, use it to update game logic
void Game::Update(float dTime)
{
	mGamepads.Update();
	mModeMgr.Update(dTime);
}

//called over and over, use it to render things
void Game::Render(float dTime)
{
	mD3D.BeginRender(Colours::Black);


	CommonStates dxstate(&mD3D.GetDevice());
	mpSB->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &mD3D.GetWrapSampler());
	mModeMgr.Render(dTime, *mpSB);
	mMenuMgr.Render(dTime, *mpSB, mD3D.GetCache(), mMKIn);
	mpSB->End();


	mD3D.EndRender();
	mMKIn.PostProcess();
}

void Game::ConfigureUI()
{
	mMenuMgr.Reset();
	vector<TexCache::TexData::Sprite> frames{
		{{10,10},true,{192,94,192 + 99,94 + 100}},		//blue_panel
		{{0,0},false,{0,94,0 + 190,94 + 49}},	//blue_button00
		{{0,0},false,{190,49,190 + 190,49 + 45}},	//blue_button01
		{{0,0},false,{190,0,190 + 190,0 + 49}},	//blue_button02
	};
	mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), "data/blueSheet.dds", "data/blueSheet.dds", false, &frames);
	mMenuMgr.LoadFont(L"data/fonts/comicSansMS.spritefont", "comicsans", 12);
	//create an empty menu page for the intro UI
	MenuNode& root = mMenuMgr.AddMenu("Intro", 512, 256);
	BuildTwoButtonUI(mMenuMgr, root, 370, 120, "start", "start button", "quit", "quit button");
	MenuNode& root2 = mMenuMgr.AddMenu("GameOver", 512, 256);
	BuildTwoButtonUI(mMenuMgr, root2, 370, 120, "restart", "restart button", "quit", "quit button");
}


//****************************************************************



//********************************************************************
const std::string IntroMode::MODE_NAME = "INTRO";

IntroMode::IntroMode()
	: mSpr(Game::Get().GetD3D())
{
	mSpr.SetTex(*Game::Get().GetD3D().GetCache().LoadTexture(&Game::Get().GetD3D().GetDevice(), "start1.dds", "start1"));
	mSpr.SetScale(Vector2(WinUtil::Get().GetClientWidth() / mSpr.GetTexData().dim.x, WinUtil::Get().GetClientHeight() / mSpr.GetTexData().dim.y));
	
	MenuMgr::Handler h1{ [this](MenuNode& node, MenuNode::Event etype) {HandleUIEvent(node, etype); } };
	MenuMgr& mgr = Game::Get().GetMenuMgr();
	mgr.AddEventHandler("Intro", "quit button", MenuNode::Event::CLICK, h1);
	mgr.AddEventHandler("Intro", "start button", MenuNode::Event::CLICK, h1);
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

void IntroMode::HandleUIEvent(MenuNode& node, MenuNode::Event etype)
{
	if (node.mName == "quit button" && etype == MenuNode::Event::CLICK)
	{
		PostQuitMessage(0);
	}
	else if (node.mName == "start button" && etype == MenuNode::Event::CLICK)
	{
		Game::Get().GetModeMgr().SwitchMode(PlayMode::MODE_NAME);
	}
}

bool IntroMode::Exit()
{
	Game::Get().GetMenuMgr().HideMenu();
	return true;
}

void IntroMode::Enter()
{
	Game::Get().GetMenuMgr().ShowMenu("Intro");
}

//********************************************************************
const std::string GameOverMode::MODE_NAME = "GAMEOVER";

GameOverMode::GameOverMode()
	: mSpr(Game::Get().GetD3D())
{
	mSpr.SetTex(*Game::Get().GetD3D().GetCache().LoadTexture(&Game::Get().GetD3D().GetDevice(), "game_over.dds", "gameover"));
	float xscale = (WinUtil::Get().GetClientWidth() * 0.8f) / mSpr.GetTexData().dim.x;
	mSpr.SetScale(Vector2( xscale, xscale));
	
	MenuMgr::Handler h1{ [this](MenuNode& node, MenuNode::Event etype) {HandleUIEvent(node, etype); } };
	MenuMgr& mgr = Game::Get().GetMenuMgr();
	mgr.AddEventHandler("GameOver", "quit button", MenuNode::Event::CLICK, h1);
	mgr.AddEventHandler("GameOver", "restart button", MenuNode::Event::CLICK, h1);
}
void GameOverMode::Update(float dTime)
{
	pointsScored = PlayMode().RecordScore;
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

void GameOverMode::HandleUIEvent(MenuNode& node, MenuNode::Event etype)
{
	if (node.mName == "quit button" && etype == MenuNode::Event::CLICK)
	{
		PostQuitMessage(0);
	}
	else if (node.mName == "restart button" && etype == MenuNode::Event::CLICK)
	{
		Game::Get().GetModeMgr().SwitchMode(IntroMode::MODE_NAME);
	}
}

bool GameOverMode::Exit()
{
	Game::Get().GetMenuMgr().HideMenu();
	return true;
}

void GameOverMode::Enter()
{
	Game::Get().GetMenuMgr().ShowMenu("GameOver");
}
