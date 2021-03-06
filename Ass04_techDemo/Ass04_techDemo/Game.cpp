#include "Game.h"
#include "WindowUtils.h"
#include "CommonStates.h"
#include "PlayMode.h"
#include "UIConfig.h"
#include "MenuMgr.h"
#include "MenuNodes.h"
#include "Definitions.h"

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
	// UI Textures and frames 
	vector<TexCache::TexData::Sprite> mTexFrames{
		{{528,270},false,{528,270,528+480,270+270}},	//panel
		{{328,0},false,{328,0,328+200,165}},			//Logo
		{{0,64},false,{0,64,256,64+64}},				//button_rect
		{{0,0},false,{0,0,256,64}},						//button_rect_pressed
		{{0,192},false,{0,192,200,192+128}},			//button_circle
		{{0,192},false,{0,192,200,192+128}},			//button_circle_pressed
	};
	mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), UI_SHEET_TEXTURE, UI_SHEET_TEXTURE, false, &mTexFrames);
	mMenuMgr.LoadFont(FONT_AGENCYFB_FILEPATH, "agencyfb", 48);

	// Main Menu UI
	//create an empty menu page for the intro UI
	MenuNode& root = mMenuMgr.AddMenu("Intro", 1280, 720);
	BuildMainMenuUI(mMenuMgr, root, 900, 600, 48,
		"MAIN MENU", GAME_TITLE,
		"EXTRAS", "extras button",
		"OPTIONS", "options button",
		"START", "start button",
		"RULES", "Rules button",
		"QUIT", "quit button");

	// GameOver Menu UI
	MenuNode& root2 = mMenuMgr.AddMenu("GameOver", 1280, 720);
	BuildGameOverMenuUI(mMenuMgr, root2, 900, 600, 48,
		"GAME OVER", GAME_TITLE,
		"SCORES", "scores button",
		"OPTIONS", "options button",
		"RESTART", "restart button",
		"RULES", "rules button",
		"QUIT", "quit button");
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

	float xscale = (WinUtil::Get().GetClientWidth() / mSpr.GetTexData().dim.x) * 0.5f;
	float yscale = (WinUtil::Get().GetClientHeight() / mSpr.GetTexData().dim.y) * 0.35f;
	mSpr.SetScale(Vector2(xscale, yscale));

	mSpr.mPos.x = (WinUtil::Get().GetClientWidth() * 0.5f) - (mSpr.GetScreenSize().x / 2);
	mSpr.mPos.y = (WinUtil::Get().GetClientHeight() * 0.5f) - (mSpr.GetScreenSize().y / 2);

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
