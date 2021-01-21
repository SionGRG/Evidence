#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <vector>

#include "WindowUtils.h"
#include "Definitions.h"
#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


//if ALT+ENTER or resize or drag window we might want do
//something like pause the game perhaps, but we definitely
//need to let D3D know what's happened (OnResize_Default).
void OnResize(int screenWidth, int screenHeight, MyD3D& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);
}

//messages come from windows all the time, should we respond to any specific ones?
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			break;
		}
		Game::Get().ProcessKey((char)wParam);
		break;
	case WM_INPUT:
		Game::Get().mMKIn.MessageEvent((HRAWINPUT)lParam);
		break;
	}

	//default message handling (resize window, full screen, etc)
	return WinUtil::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	//int w(512), h(256);
	//int defaults[] = { 640,480, 800,600, 1024,768, 1280,1024 };
		//WinUtil::ChooseRes(w, h, defaults, 4);
	new WinUtil();
	if (!WinUtil::Get().InitMainWindow(SCREEN_WIDTH, SCREEN_HEIGHT, hInstance, GAME_TITLE, MainWndProc, true))
		assert(false);
	MyD3D d3d;
	if (!d3d.InitDirect3D(OnResize))
		assert(false);
	d3d.GetCache().SetAssetPath("data/");
	WinUtil::Get().SetD3D(d3d);
	new Game(d3d);

	bool canUpdateRender;
	float dTime = 0;
	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender && dTime>0)
		{
			Game::Get().Update(dTime);
			Game::Get().Render(dTime);
		}
		dTime = WinUtil::Get().EndLoop(canUpdateRender);
	}

	delete &Game::Get();
	d3d.ReleaseD3D(true);	
	delete &WinUtil::Get();
	return 0;
}

