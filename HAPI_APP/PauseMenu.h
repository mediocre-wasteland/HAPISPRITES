#pragma once
#include <HAPISprites_Lib.h>
using namespace HAPISPACE;
#include <HAPISprites_UI.h>
using namespace HAPI_UI_SPACE;
// ^ Include + Use Second
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

