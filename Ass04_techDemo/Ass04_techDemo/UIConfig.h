#pragma once
#include <string>

#include "MenuMgr.h"


/*
Creates a small window frame with two buttons in it
The code to configure the elements is long and cumbersome so 
wrapping in a reusable function like this makes sense.
mgr - the one and only menumgr
root - a root node that this two button setup can attach to, so if you want this two button group 
on ten different menu screens then just call it ten times and attach to ten different roots
b1,b2 - what the buttons should have written on them
b1Name,b2Name - this is the internal logical name for the buttons, so you cna hook up event handlers to them
*/
void BuildTwoButtonUI(MenuMgr& mgr, MenuNode& root, float x, float y, const std::string& b1, const std::string& b1Name, const std::string& b2, const std::string& b2Name);



/*
	Creates a window frame with the menu buttons in it
	The code to configure the elements is long and cumbersome so
	wrapping in a reusable function like this makes sense.
	mgr - the one and only menumgr
	root - a root node that this menu button setup can attach to, so if you want this
	menu button group on ten different menu screens then just call it ten times and attach to ten different roots
	mT - the menu title
	mTName - the internal logical name for the menu title
	mL - the menu logo
	mLName - the internal logical name for the menu title
	b1,b2,b3... - what the buttons should have written on them
	b1Name,b2Name,b3Name... - this is the internal logical name for the buttons, so you can hook up event handlers to them
*/
void BuildMainMenuUI(MenuMgr& mgr, MenuNode& root, float x, float y,
	const std::string& mT, const std::string& mL,
	const std::string& b1, const std::string& b1Name,
	const std::string& b2, const std::string& b2Name,
	const std::string& b3, const std::string& b3Name,
	const std::string& b4, const std::string& b4Name,
	const std::string& b5, const std::string& b5Name
);