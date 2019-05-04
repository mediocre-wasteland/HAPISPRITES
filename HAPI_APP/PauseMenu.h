#pragma once
#include <HAPISprites_Lib.h>
#include <HAPISprites_UI.h>
using namespace HAPISPACE;
using namespace HAPI_UI_SPACE;

class PauseMenu : public IHapiSpritesUIListener, IHapiSpritesInputListener
{
public:
	std::string pauseMenuName;
	PauseMenu();
	~PauseMenu();

	void UI_ButtonPressed(UIWindow& window, const std::string& buttonName, int* userId) override; // Checks if Button has been pressed.
	void OnKeyEvent(EKeyEvent keyEvent, BYTE keyCode) override final; // Checks what Key the user has pressed.
	void OnMouseEvent(EMouseEvent mouseEvent, const MouseData& mouseData) override final {}; // Checks what Mouse button the 

	bool Run();
	bool Initialise();
	bool paused{ false };
};