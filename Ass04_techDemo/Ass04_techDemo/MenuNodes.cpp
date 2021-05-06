
#include "SpriteFont.h"

#include "D3DUtil.h"
#include "MenuNodes.h"
#include "Input.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void MenuPage::Render(const ExtraData& rdata, const Vector2& offset, const Vector2& scale)
{
	Vector2 pos = { offset.x + mX * scale.x, offset.y + mY * scale.y };
	MenuNode::Render(rdata, pos, scale);
};


//*******************************************************
void MenuButton::Render(const ExtraData& rdata, const Vector2& offset, const Vector2& scale)
{
	//where is the button?
	const TexCache::TexData& data = rdata.texCache.Get(buttons[NORMAL].textureName);
	const TexCache::TexData::Sprite* sprite = nullptr;
	if (!data.frames.empty() && (int)data.frames.size() > buttons[NORMAL].spriteID)
		sprite = &data.GetSprite(buttons[NORMAL].spriteID);
	RECT dest;
	GetImageDest(dest, sprite, offset, scale);

	//what is the mouse doing?
	Vector2 spos = rdata.mouseAndKeys.GetMousePos(true);
	bool over = (spos.x >= dest.left && spos.x <= dest.right && spos.y >= dest.top && spos.y <= dest.bottom);
	if (over && rdata.mouseAndKeys.GetMouseButton(MouseAndKeys::ButtonT::LBUTTON))
	{
		//pressed
		rdata.texCache.Render(rdata.spriteBatch, buttons[PRESSED].textureName, dest, buttons[PRESSED].spriteID, buttons[PRESSED].colour);
		mWasDown = true;
	}
	else if (over)
	{
		//hover
		rdata.texCache.Render(rdata.spriteBatch, buttons[HOVER].textureName, dest, buttons[HOVER].spriteID, buttons[HOVER].colour);
		if (mWasDown)
			rdata.menuMgr.TriggerEvent(*this, MenuNode::Event::CLICK);
		mWasDown = false;
	}
	else
	{
		//normal
		rdata.texCache.Render(rdata.spriteBatch, buttons[NORMAL].textureName, dest, buttons[NORMAL].spriteID, buttons[NORMAL].colour);
		mWasDown = false;
	}
	MenuNode::Render(rdata, Vector2((float)dest.left, (float)dest.top), scale);
}

//***************************************************************
void MenuImage::Render(const ExtraData& rdata, const Vector2& offset, const Vector2& scale)
{
	const TexCache::TexData& data = rdata.texCache.Get(mTextureName);
	const TexCache::TexData::Sprite* sprite = &data.GetSprite(mSpriteID);
	RECT dest;
	GetImageDest(dest, sprite, offset, scale);
	rdata.texCache.Render(rdata.spriteBatch, mTextureName, dest, mSpriteID);
	MenuNode::Render(rdata, Vector2((float)dest.left, (float)dest.top), scale);
}


//*********************************************************************
Vector2 MenuText::Render(const TextData& d)
{
	RECT dest;
	MenuNode::GetImageDest(dest, d.pos, d.wh, nullptr, d.offset, d.scale);
	Vector2 npos((float)dest.left, (float)dest.top);

	//scale the text to fit the rectangle while maintaining aspect ratio
	const SpriteFont& font = d.prdata->menuMgr.GetFont(*d.pfontName, d.pitch);
	Vector2 actual = font.MeasureString(d.ptext->c_str());
	Vector2 desired{ (float)dest.right - (float)dest.left, (float)dest.bottom - (float)dest.top };
	Vector2 tscale{ desired.x / actual.x, desired.y / actual.y };
	if (tscale.x < tscale.y)
		tscale.y = tscale.x;
	else if (tscale.x > tscale.y)
		tscale.x = tscale.y;

	font.DrawString(&d.prdata->spriteBatch, d.ptext->c_str(), npos, Colours::White, 0, Vector2(0, 0), tscale, SpriteEffects_None, d.layer);
	return npos;
}


void MenuText::Render(const ExtraData& rdata, const Vector2& offset, const Vector2& scale)
{
	Vector2 pos = Render(TextData{ Vector2((float)mX, (float)mY), Vector2((float)mW, (float)mH), &rdata, offset, scale, &mFont, mPitch, &mText, MenuNode::ZDEPTH_UILAYER });
	MenuNode::Render(rdata, pos, scale);
}

//**********************************************************************************
void MenuCheckbox::Render(const ExtraData& rdata, const Vector2& offset, const Vector2& scale)
{
	Vector2 pos = { offset.x + mX * scale.x, offset.y + mY * scale.y };
	MenuNode::Render(rdata, pos, scale);
};



//***********************************************************************************
void MenuBox::Render(const ExtraData& rdata, const Vector2& offset, const Vector2& scale)
{
	Vector2 pos = { offset.x + mX * scale.x, offset.y + mY * scale.y };
	MenuNode::Render(rdata, pos, scale);
};

void MenuBox::BoxItemsPos(MenuBox::Orientation or , MenuBox::Alignment align, int mPos1, float _distance)
{
	int _mBoxItemsSize = MenuBox::mChildren.size();
	mBoxItems = MenuBox::mChildren;
	if (or == MenuBox::Orientation::HORIZONTAL)
	{
		mBoxItems.at(0)->mX = mPos1;
		for (int i = 1; i < _mBoxItemsSize; i++)
		{
			mBoxItems.at(i)->mX = _distance + mBoxItems.at(i - 1)->mX + mBoxItems.at(i - 1)->mW;
		}

		// set the y position of the elements
		for (int i = 0; i < _mBoxItemsSize; i++)
		{
			if (align == MenuBox::Alignment::TOP)
			{
				mBoxItems.at(i)->mY = this->mY;
			}
			else if (align == MenuBox::Alignment::CENTER)
			{
				mBoxItems.at(i)->mY = this->mH / 2 - (mBoxItems.at(i)->mH / 2);
			}
			else if (align == MenuBox::Alignment::BOTTOM)
			{
				mBoxItems.at(i)->mY = this->mH - (mBoxItems.at(i)->mH);
			}
		}
	}
	if (or == MenuBox::Orientation::VERTICAL)
	{
		mBoxItems.at(0)->mY = mPos1;
		for (int i = 1; i < _mBoxItemsSize; i++)
		{
			mBoxItems.at(i)->mY = _distance + mBoxItems.at(i - 1)->mY + mBoxItems.at(i - 1)->mH;
		}

		// set the x position of the elements
		for (int i = 1; i < _mBoxItemsSize; i++)
		{
			// Item alignement :: LEFT or CENTER or RIGHT
			if (align == MenuBox::Alignment::LEFT)
			{
				mBoxItems.at(i)->mX = this->mX;
			}
			else if (align == MenuBox::Alignment::CENTER)
			{
				mBoxItems.at(i)->mX = this->mW / 2 - (mBoxItems.at(i)->mW / 2);
			}
			else if (align == MenuBox::Alignment::RIGHT)
			{
				mBoxItems.at(i)->mX = this->mW - (mBoxItems.at(i)->mW);
			}
		}
	}
}