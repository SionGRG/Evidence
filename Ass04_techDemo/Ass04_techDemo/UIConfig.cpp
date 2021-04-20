#include <d3d11.h>

#include "UIConfig.h"
#include "D3D.h"
#include "MenuNodes.h"
#include "Definitions.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//**************************************************************************
void BuildTwoButtonUI(MenuMgr& mgr, MenuNode& root, float x, float y, const string& b1, const string& b1Name, const string& b2, const string& b2Name)
{
	//add a background node
	MenuImage* pIm = dynamic_cast<MenuImage*>(&mgr.CreateNode(MenuNode::Type::IMAGE));
	assert(pIm);
	pIm->mName = "Background";
	pIm->mX = 370;
	pIm->mY = 120;
	pIm->mW = 120;
	pIm->mH = 125;
	pIm->SetParent(root);
	pIm->mTextureName = "data/blueSheet.dds";
	//pIm->mSpriteName = "blue_panel";
	pIm->mSpriteID = 0;

	MenuButton* pB = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB);
	pB->buttons[MenuButton::NORMAL].spriteID = 1;
	pB->buttons[MenuButton::NORMAL].textureName = "data/blueSheet.dds";
	pB->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB->buttons[MenuButton::HOVER].spriteID = 1;
	pB->buttons[MenuButton::HOVER].textureName = "data/blueSheet.dds";
	pB->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 1);
	pB->buttons[MenuButton::PRESSED].spriteID = 2;
	pB->buttons[MenuButton::PRESSED].textureName = "data/blueSheet.dds";
	pB->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 1);
	pB->mName = b1Name;
	pB->mX = 20;
	pB->mY = 20;
	pB->mW = 75;
	pB->mH = 40;
	pB->SetParent(*pIm);


	MenuText* pT = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT);
	pT->mName = "title";
	pT->mX = 5;
	pT->mY = 5;
	pT->mW = 60;
	pT->mH = 30;
	pT->mText = b1;
	pT->mFont = "comicsans";
	pT->mPitch = 12;
	pT->SetParent(*pB);


	MenuButton* pB3 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB3);
	pB3->buttons[MenuButton::NORMAL].spriteID = 1;
	pB3->buttons[MenuButton::NORMAL].textureName = "data/blueSheet.dds";
	pB3->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB3->buttons[MenuButton::HOVER].spriteID = 1;
	pB3->buttons[MenuButton::HOVER].textureName = "data/blueSheet.dds";
	pB3->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 1);
	pB3->buttons[MenuButton::PRESSED].spriteID = 2;
	pB3->buttons[MenuButton::PRESSED].textureName = "data/blueSheet.dds";
	pB3->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 1);
	pB3->mName = b2Name;
	pB3->mX = 20;
	pB3->mY = 70;
	pB3->mW = 75;
	pB3->mH = 40;
	pB3->SetParent(*pIm);

	pT = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT);
	pT->mName = "title";
	pT->mX = 5;
	pT->mY = 5;
	pT->mW = 60;
	pT->mH = 30;
	pT->mText = b2;
	pT->mFont = "comicsans";
	pT->mPitch = 12;
	pT->SetParent(*pB3);
}

//******************************************************************************
void BuildMainMenuUI(MenuMgr& mgr, MenuNode& root, float x, float y,
	int mTxtPitch, const std::string& mT, const std::string& mL,
	const std::string& b1, const std::string& b1Name,
	const std::string& b2, const std::string& b2Name,
	const std::string& b3, const std::string& b3Name,
	const std::string& b4, const std::string& b4Name,
	const std::string& b5, const std::string& b5Name)
{
	//add a background node
	MenuImage* pIm = dynamic_cast<MenuImage*>(&mgr.CreateNode(MenuNode::Type::IMAGE));
	assert(pIm);
	pIm->mName = "Background";
	pIm->mW = SCREEN_WIDTH - 20;
	pIm->mH = SCREEN_HEIGHT - 20;
	pIm->mX = 10;
	pIm->mY = 10;
	pIm->SetParent(root);
	pIm->mTextureName = UI_SHEET_TEXTURE;
	//pIm->mSpriteName = "blue_panel";
	pIm->mSpriteID = 0;

	// Vertical box containing the all the menu UI 
	MenuBox* pVBX = dynamic_cast<MenuBox*>(&mgr.CreateNode(MenuNode::Type::MENUBOX));
	assert(pVBX);
	pVBX->SetParent(*pIm);
	pVBX->mX = 10;
	pVBX->mY = 20;
	pVBX->mW = pIm->mW;
	pVBX->mH = 700;

	/* ************* Menu Title section ************* */

	// Add Menu title
	MenuText* pmT = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pmT);
	pmT->mName = "menuTitle";
	pmT->mW = 300;
	pmT->mH = 100;
	pmT->mX = (pVBX->mW / 2) - (pmT->mW / 2);
	pmT->mY = 1;
	pmT->mText = mT;
	pmT->mFont = "agencyfb";
	pmT->mPitch = mTxtPitch;
	pmT->SetParent(*pVBX);

	/* ************* Menu Game logo section ************* */


	// Horizontal box the logo section
	MenuBox* pVBXLg = dynamic_cast<MenuBox*>(&mgr.CreateNode(MenuNode::Type::MENUBOX));
	assert(pVBXLg);
	pVBXLg->SetParent(*pVBX);
	pVBXLg->mW = pVBX->mW;
	pVBXLg->mH = 250;

	// Add Game logo to the Menu
	MenuImage* pLgIm = dynamic_cast<MenuImage*>(&mgr.CreateNode(MenuNode::Type::IMAGE));
	assert(pLgIm);
	pLgIm->mName = mL;
	pLgIm->mW = 200;
	pLgIm->mH = 165;
	pLgIm->mX = pVBXLg->mW / 2 - pLgIm->mW / 2;
	pLgIm->mY = 400;
	pLgIm->mTextureName = UI_SHEET_TEXTURE;
	pLgIm->mSpriteID = 1;
	pLgIm->SetParent(*pVBXLg);

	// Set the position of the items contained in the Vertical box
	pVBXLg->BoxItemsPos(MenuBox::Orientation::VERTICAL, MenuBox::Alignment::CENTER, 40, 50);

	/* ************* Menu Buttons section ************* */

	// Horizontal box for the menu buttons
	MenuBox* pHBX = dynamic_cast<MenuBox*>(&mgr.CreateNode(MenuNode::Type::MENUBOX));
	assert(pHBX);
	pHBX->SetParent(*pVBX);
	pHBX->mW = pVBX->mW;
	pHBX->mH = 200;

	// Add Menu Buttons
	MenuButton* pB1 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB1);
	pB1->buttons[MenuButton::NORMAL].spriteID = 2;
	pB1->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB1->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB1->buttons[MenuButton::HOVER].spriteID = 2;
	pB1->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB1->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB1->buttons[MenuButton::PRESSED].spriteID = 3;
	pB1->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB1->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB1->mName = b1Name;
	pB1->mW = 200;
	pB1->mH = 70;
	pB1->SetParent(*pHBX);

	// Button text
	MenuText* pT1 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT1);
	pT1->SetParent(*pB1);
	pT1->mFont = "agencyfb";
	pT1->mName = "btnName";
	pT1->mText = b1;
	pT1->mPitch = mTxtPitch;
	pT1->mW = pB1->mW * .7f;
	pT1->mH = pB1->mH * .9f;
	pT1->mX = pB1->mW * .5f - pT1->mW * .5f;
	pT1->mY = pB1->mH * .5f - pT1->mH * .5f;

	// Add Menu Buttons
	MenuButton* pB2 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB2);
	pB2->SetParent(*pHBX);
	pB2->buttons[MenuButton::NORMAL].spriteID = 2;
	pB2->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB2->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB2->buttons[MenuButton::HOVER].spriteID = 2;
	pB2->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB2->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB2->buttons[MenuButton::PRESSED].spriteID = 3;
	pB2->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB2->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB2->mName = b2Name;
	pB2->mW = 200;
	pB2->mH = 70;
	
	// Button text
	MenuText* pT2 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT2);
	pT2->SetParent(*pB2);
	pT2->mFont = "agencyfb";
	pT2->mName = "btnName";
	pT2->mText = b2;
	pT2->mPitch = mTxtPitch;
	pT2->mW = pB2->mW * .7f;
	pT2->mH = pB2->mH * .9f;
	pT2->mX = pB2->mW * .5f - pT2->mW * .5f;
	pT2->mY = pB2->mH * .5f - pT2->mH * .5f;

	// Add Menu Buttons
	MenuButton* pB3 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB3);
	pB3->SetParent(*pHBX);
	pB3->buttons[MenuButton::NORMAL].spriteID = 4;
	pB3->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB3->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB3->buttons[MenuButton::HOVER].spriteID = 4;
	pB3->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB3->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB3->buttons[MenuButton::PRESSED].spriteID = 5;
	pB3->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB3->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB3->mName = b3Name;
	pB3->mW = 200;
	pB3->mH = 150;

	// Button text
	MenuText* pT3 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT3);
	pT3->SetParent(*pB3);
	pT3->mFont = "agencyfb";
	pT3->mName = "btnName";
	pT3->mText = b3;
	pT3->mPitch = mTxtPitch;
	pT3->mW = pB3->mW * .7f;
	pT3->mH = pB3->mH * .9f;
	pT3->mX = pB3->mW * .5f - pT3->mW * .5f;
	pT3->mY = pB3->mH * .5f - pT3->mH * .3f;

	// Add Menu Buttons
	MenuButton* pB4 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB4);
	pB4->SetParent(*pHBX);
	pB4->buttons[MenuButton::NORMAL].spriteID = 2;
	pB4->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB4->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB4->buttons[MenuButton::HOVER].spriteID = 2;
	pB4->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB4->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB4->buttons[MenuButton::PRESSED].spriteID = 3;
	pB4->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB4->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB4->mName = b4Name;
	pB4->mW = 200;
	pB4->mH = 70;

	// Button text
	MenuText* pT4 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT4);
	pT4->SetParent(*pB4);
	pT4->mFont = "agencyfb";
	pT4->mName = "btnName";
	pT4->mText = b4;
	pT4->mPitch = mTxtPitch;
	pT4->mW = pB4->mW * .7f;
	pT4->mH = pB4->mH * .9f;
	pT4->mX = pB4->mW * .5f - pT4->mW * .45f;
	pT4->mY = pB4->mH * .5f - pT4->mH * .5f;

	// Add Menu Buttons
	MenuButton* pB5 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB5);
	pB5->buttons[MenuButton::NORMAL].spriteID = 2;
	pB5->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB5->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB5->buttons[MenuButton::HOVER].spriteID = 2;
	pB5->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB5->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB5->buttons[MenuButton::PRESSED].spriteID = 3;
	pB5->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB5->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB5->mName = b5Name;
	pB5->mW = 200;
	pB5->mH = 70;
	pB5->SetParent(*pHBX);

	// Button text
	MenuText* pT5 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT5);
	pT5->SetParent(*pB5);
	pT5->mFont = "agencyfb";
	pT5->mName = "btnName";
	pT5->mText = b5;
	pT5->mPitch = mTxtPitch;
	pT5->mW = pB5->mW * .7f;
	pT5->mH = pB5->mH * .9f;
	pT5->mX = pB5->mW * .5f - pT5->mW * .3f;
	pT5->mY = pB5->mH * .5f - pT5->mH * .5f;

	// Set the position of the items contained in the horizontal box
	pHBX->BoxItemsPos(MenuBox::Orientation::HORIZONTAL, MenuBox::Alignment::CENTER, 20, 50);

	// Set the position of the items contained in the vertical box
	pVBX->BoxItemsPos(MenuBox::Orientation::VERTICAL, MenuBox::Alignment::CENTER, 20, 50);
}

//******************************************************************************
void BuildGameOverMenuUI(MenuMgr& mgr, MenuNode& root, float x, float y,
	int mTxtPitch, const std::string& mT, const std::string& mL,
	const std::string& b1, const std::string& b1Name,
	const std::string& b2, const std::string& b2Name,
	const std::string& b3, const std::string& b3Name,
	const std::string& b4, const std::string& b4Name,
	const std::string& b5, const std::string& b5Name)
{
	//add a background node
	MenuImage* pIm = dynamic_cast<MenuImage*>(&mgr.CreateNode(MenuNode::Type::IMAGE));
	assert(pIm);
	pIm->mName = "Background";
	pIm->mW = SCREEN_WIDTH - 20;
	pIm->mH = SCREEN_HEIGHT - 20;
	pIm->mX = 10;
	pIm->mY = 10;
	pIm->SetParent(root);
	pIm->mTextureName = UI_SHEET_TEXTURE;
	//pIm->mSpriteName = "blue_panel";
	pIm->mSpriteID = 0;

	// Vertical box containing the all the menu UI 
	MenuBox* pVBX = dynamic_cast<MenuBox*>(&mgr.CreateNode(MenuNode::Type::MENUBOX));
	assert(pVBX);
	pVBX->SetParent(*pIm);
	pVBX->mX = 10;
	pVBX->mY = 20;
	pVBX->mW = pIm->mW;
	pVBX->mH = 700;

	/* ************* Menu Title section ************* */

	// Add Menu title
	MenuText* pmT = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pmT);
	pmT->mName = "menuTitle";
	pmT->mW = 300;
	pmT->mH = 100;
	pmT->mX = (pVBX->mW / 2) - (pmT->mW / 2);
	pmT->mY = 1;
	pmT->mText = mT;
	pmT->mFont = "agencyfb";
	pmT->mPitch = mTxtPitch;
	pmT->SetParent(*pVBX);

	/* ************* Menu Game logo section ************* */


	// Horizontal box the logo section
	MenuBox* pVBXLg = dynamic_cast<MenuBox*>(&mgr.CreateNode(MenuNode::Type::MENUBOX));
	assert(pVBXLg);
	pVBXLg->SetParent(*pVBX);
	pVBXLg->mW = pVBX->mW;
	pVBXLg->mH = 250;

	// Add Game logo to the Menu
	MenuImage* pLgIm = dynamic_cast<MenuImage*>(&mgr.CreateNode(MenuNode::Type::IMAGE));
	assert(pLgIm);
	pLgIm->mName = mL;
	pLgIm->mW = 200;
	pLgIm->mH = 165;
	pLgIm->mX = pVBXLg->mW / 2 - pLgIm->mW / 2;
	pLgIm->mY = 400;
	pLgIm->mTextureName = UI_SHEET_TEXTURE;
	pLgIm->mSpriteID = 1;
	pLgIm->SetParent(*pVBXLg);

	// Set the position of the items contained in the Vertical box
	pVBXLg->BoxItemsPos(MenuBox::Orientation::VERTICAL, MenuBox::Alignment::CENTER, 40, 50);

	/* ************* Menu Buttons section ************* */

	// Horizontal box for the menu buttons
	MenuBox* pHBX = dynamic_cast<MenuBox*>(&mgr.CreateNode(MenuNode::Type::MENUBOX));
	assert(pHBX);
	pHBX->SetParent(*pVBX);
	pHBX->mW = pVBX->mW;
	pHBX->mH = 200;

	// Add Menu Buttons
	MenuButton* pB1 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB1);
	pB1->buttons[MenuButton::NORMAL].spriteID = 2;
	pB1->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB1->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB1->buttons[MenuButton::HOVER].spriteID = 2;
	pB1->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB1->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB1->buttons[MenuButton::PRESSED].spriteID = 3;
	pB1->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB1->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB1->mName = b1Name;
	pB1->mW = 200;
	pB1->mH = 70;
	pB1->SetParent(*pHBX);

	// Button text
	MenuText* pT1 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT1);
	pT1->SetParent(*pB1);
	pT1->mFont = "agencyfb";
	pT1->mName = "btnName";
	pT1->mText = b1;
	pT1->mPitch = mTxtPitch;
	pT1->mW = pB1->mW * .7f;
	pT1->mH = pB1->mH * .9f;
	pT1->mX = pB1->mW * .5f - pT1->mW * .5f;
	pT1->mY = pB1->mH * .5f - pT1->mH * .5f;

	// Add Menu Buttons
	MenuButton* pB2 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB2);
	pB2->SetParent(*pHBX);
	pB2->buttons[MenuButton::NORMAL].spriteID = 2;
	pB2->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB2->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB2->buttons[MenuButton::HOVER].spriteID = 2;
	pB2->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB2->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB2->buttons[MenuButton::PRESSED].spriteID = 3;
	pB2->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB2->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB2->mName = b2Name;
	pB2->mW = 200;
	pB2->mH = 70;

	// Button text
	MenuText* pT2 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT2);
	pT2->SetParent(*pB2);
	pT2->mFont = "agencyfb";
	pT2->mName = "btnName";
	pT2->mText = b2;
	pT2->mPitch = mTxtPitch;
	pT2->mW = pB2->mW * .7f;
	pT2->mH = pB2->mH * .9f;
	pT2->mX = pB2->mW * .5f - pT2->mW * .5f;
	pT2->mY = pB2->mH * .5f - pT2->mH * .5f;

	// Add Menu Buttons
	MenuButton* pB3 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB3);
	pB3->SetParent(*pHBX);
	pB3->buttons[MenuButton::NORMAL].spriteID = 4;
	pB3->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB3->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB3->buttons[MenuButton::HOVER].spriteID = 4;
	pB3->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB3->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB3->buttons[MenuButton::PRESSED].spriteID = 5;
	pB3->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB3->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB3->mName = b3Name;
	pB3->mW = 200;
	pB3->mH = 150;

	// Button text
	MenuText* pT3 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT3);
	pT3->SetParent(*pB3);
	pT3->mFont = "agencyfb";
	pT3->mName = "btnName";
	pT3->mText = b3;
	pT3->mPitch = mTxtPitch;
	pT3->mW = pB3->mW * .75f;
	pT3->mH = pB3->mH * .95f;
	pT3->mX = pB3->mW * .5f - pT3->mW * .5f;
	pT3->mY = pB3->mH * .5f - pT3->mH * .25f;

	// Add Menu Buttons
	MenuButton* pB4 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB4);
	pB4->SetParent(*pHBX);
	pB4->buttons[MenuButton::NORMAL].spriteID = 2;
	pB4->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB4->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB4->buttons[MenuButton::HOVER].spriteID = 2;
	pB4->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB4->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB4->buttons[MenuButton::PRESSED].spriteID = 3;
	pB4->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB4->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB4->mName = b4Name;
	pB4->mW = 200;
	pB4->mH = 70;

	// Button text
	MenuText* pT4 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT4);
	pT4->SetParent(*pB4);
	pT4->mFont = "agencyfb";
	pT4->mName = "btnName";
	pT4->mText = b4;
	pT4->mPitch = mTxtPitch;
	pT4->mW = pB4->mW * .7f;
	pT4->mH = pB4->mH * .9f;
	pT4->mX = pB4->mW * .5f - pT4->mW * .45f;
	pT4->mY = pB4->mH * .5f - pT4->mH * .5f;

	// Add Menu Buttons
	MenuButton* pB5 = dynamic_cast<MenuButton*>(&mgr.CreateNode(MenuNode::Type::BUTTON));
	assert(pB5);
	pB5->buttons[MenuButton::NORMAL].spriteID = 2;
	pB5->buttons[MenuButton::NORMAL].textureName = UI_SHEET_TEXTURE;
	pB5->buttons[MenuButton::NORMAL].colour = Vector4(1, 1, 1, 1);
	pB5->buttons[MenuButton::HOVER].spriteID = 2;
	pB5->buttons[MenuButton::HOVER].textureName = UI_SHEET_TEXTURE;
	pB5->buttons[MenuButton::HOVER].colour = Vector4(0.95f, 0.95f, 0.95f, 0.85f);
	pB5->buttons[MenuButton::PRESSED].spriteID = 3;
	pB5->buttons[MenuButton::PRESSED].textureName = UI_SHEET_TEXTURE;
	pB5->buttons[MenuButton::PRESSED].colour = Vector4(0.95f, 0.95f, 0.95f, 0.9f);
	pB5->mName = b5Name;
	pB5->mW = 200;
	pB5->mH = 70;
	pB5->SetParent(*pHBX);

	// Button text
	MenuText* pT5 = dynamic_cast<MenuText*>(&mgr.CreateNode(MenuNode::Type::TEXT));
	assert(pT5);
	pT5->SetParent(*pB5);
	pT5->mFont = "agencyfb";
	pT5->mName = "btnName";
	pT5->mText = b5;
	pT5->mPitch = mTxtPitch;
	pT5->mW = pB5->mW * .7f;
	pT5->mH = pB5->mH * .9f;
	pT5->mX = pB5->mW * .5f - pT5->mW * .3f;
	pT5->mY = pB5->mH * .5f - pT5->mH * .5f;

	// Set the position of the items contained in the horizontal box
	pHBX->BoxItemsPos(MenuBox::Orientation::HORIZONTAL, MenuBox::Alignment::CENTER, 20, 50);

	// Set the position of the items contained in the vertical box
	pVBX->BoxItemsPos(MenuBox::Orientation::VERTICAL, MenuBox::Alignment::CENTER, 20, 50);
}