#pragma once
#include <HAPISprites_Lib.h>
#include <HAPISprites_UI.h>
#include "Map.h"
using namespace HAPISPACE;
using namespace HAPI_UI_SPACE;

class MainMenuUi : public IHapiSpritesUIListener, IHapiSpritesInputListener
{
public:
	MainMenuUi();
	~MainMenuUi();
	bool Run();
	bool Initialise(Map* gameMap);
	bool Play();
	bool GetPlay() { return play; };
	void Update();
	void UI_ButtonPressed(UIWindow& window, const std::string& buttonName, int* userId) override;
	void OnKeyEvent(EKeyEvent keyEvent, BYTE keyCode) override final;
	void OnMouseEvent(EMouseEvent mouseEvent, const MouseData& mouseData) override final {};

private:
	//Screen Resolution
	int screenWidth{ 1280 };
	int screenHeight{ 832 };
	RectangleI screenRect;
	Map* mapMainMenu;
	bool play{ false };
	bool isMainMenu{ true };
	bool isOptionsMenu{ false };
	bool isCreditsMenu{ false };
	std::string mainMenuName;
	std::string optionsMenuName;
	std::string creditsMenuName;
};


