#pragma once

#include "MenuMgr.h"

//a non graphical logical root object, one for each distinct menu screen
class MenuPage : public MenuNode
{
public:
	MenuPage() : MenuNode(MenuNode::Type::ROOT) {};
	void Render(const ExtraData& rdata, const DirectX::SimpleMath::Vector2& offset, const DirectX::SimpleMath::Vector2& scale) override;
};

//a 2D image
class MenuImage : public MenuNode
{
public:
	MenuImage() : MenuNode(MenuNode::Type::IMAGE) {};
	void Render(const ExtraData& rdata, const DirectX::SimpleMath::Vector2& offset, const DirectX::SimpleMath::Vector2& scale) override;

	int mSpriteID;
	std::string mTextureName;
};

//a clickable button with text
class MenuButton : public MenuNode
{
public:
	MenuButton() : MenuNode(MenuNode::Type::BUTTON) {};
	void Render(const ExtraData& rdata, const DirectX::SimpleMath::Vector2& offset, const DirectX::SimpleMath::Vector2& scale) override;

	std::string mText;
	struct {
		//std::string spriteName;
		int spriteID = 0;
		std::string textureName;
		DirectX::SimpleMath::Vector4 colour{ 1,1,1,1 };
	}buttons[3];
	enum { PRESSED = 0, NORMAL = 1, HOVER = 2 };

private:
	bool mWasDown = false;
};

//single or multi-line text
class MenuText : public MenuNode
{
public:
	struct TextData {
		DirectX::SimpleMath::Vector2 pos;
		DirectX::SimpleMath::Vector2 wh;
		const ExtraData* prdata;
		DirectX::SimpleMath::Vector2 offset;
		DirectX::SimpleMath::Vector2 scale;
		const std::string* pfontName;
		int pitch;
		const std::string* ptext;
		float layer = 1;
	};

	std::string mText;
	std::string mFont;
	int mPitch;

	MenuText() : MenuNode(MenuNode::Type::TEXT) {};
	void Render(const ExtraData& rdata, const DirectX::SimpleMath::Vector2& offset, const DirectX::SimpleMath::Vector2& scale) override;
	static DirectX::SimpleMath::Vector2 Render(const TextData& d);

};

// A checkbox
class MenuCheckbox : public MenuNode
{
public:
	MenuCheckbox() : MenuNode(MenuNode::Type::CHECKBOX) {};
	void Render(const ExtraData& rdata, const DirectX::SimpleMath::Vector2& offset, const DirectX::SimpleMath::Vector2& scale) override;
	struct {
		int mSpriteID;
		std::string mTextureName;
	}checkboxes[2];
	enum { CHECKED = 0, NORMAL = 1, HOVER = 2 };
	bool mBoxChecked = false;
};

/*
	A box container that stores items
	forexample: buttons,texts, etc
	and are grouped and thus can be moved together
*/
class MenuBox : public MenuNode
{
public:
	MenuBox() : MenuNode(MenuNode::Type::MENUBOX) {};
	void Render(const ExtraData& rdata, const DirectX::SimpleMath::Vector2& offset, const DirectX::SimpleMath::Vector2& scale) override;
	enum class Orientation { HORIZONTAL, VERTICAL };
	enum class Alignment { LEFT, TOP, CENTER, RIGHT, BOTTOM };
	void BoxItemsPos(MenuBox::Orientation or , MenuBox::Alignment align, int mPos1, float _distance);
protected:
	std::vector<MenuNode*> mBoxItems;
private:
	struct BoxItems {
		int mBoxItemsN = 0;
		int mBoxItemID = 0;
	};
};