#pragma once
#include <HAPISprites_Lib.h>
using namespace HAPISPACE;
#include <HAPISprites_UI.h>
using namespace HAPI_UI_SPACE;
// ^ Include + Use Second
#include "Map.h"

class MainMenuUi : public IHapiSpritesUIListener
{
public:
	MainMenuUi();
	~MainMenuUi();
	bool Run();
	bool Initialise(Map* gameMap);
	void Update();
	bool Play();
	bool GetPlay() { return play; };
	void UI_ButtonPressed(UIWindow& window, const std::string& buttonName, int* userId) override; // Checks if Button has been pressed.

private:
	//Screen Resolution
	int screenWidth{ 1280 };
	int screenHeight{ 832 };
	RectangleI screenRect;
	Map* mapMainMenu;
	bool play{ false };

	std::string mainMenuName; // Main Menu
	std::string optionsMenuName; // Options Menu
	std::string creditsMenuName; // Credits Menu


};


