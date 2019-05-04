#include "PauseMenu.h"
PauseMenu::PauseMenu()
{

}
PauseMenu::~PauseMenu()
{

}

bool PauseMenu::Initialise()
{
	UI.Load("Data\\UserInterface\\PauseMenu.xml", pauseMenuName, false);

	UI.OpenWindow(pauseMenuName, false, true, pauseMenuName, EDirection::eNorth, true, EGap::eLoose, { 45,0 });

	paused = true;

	Run();

	return true;
}

void PauseMenu::UI_ButtonPressed(UIWindow& window, const std::string& buttonName, int* userId)
{
	if (buttonName == "ReturnPauseMenu")
	{
		paused = false;
		UI.CloseWindow(pauseMenuName); // Close the PauseMenu
	// Run Code to Load back to the game.
	}
	if (buttonName == "ExitPauseMenu")
	{
		HAPI_Sprites.Close();
	}
}

void PauseMenu::OnKeyEvent(EKeyEvent keyEvent, BYTE keyCode)
{
	if (keyEvent == EKeyEvent::ePress)
	{
		switch (keyCode)
		{
		case '1':
			UI.GetWindow(pauseMenuName, true)->SimulateButtonPress("ReturnPauseMenu", true);
			break;
		case '2':
			UI.GetWindow(pauseMenuName, true)->SimulateButtonPress("ExitPauseMenu", true);
			break;
		}
	}

}

bool PauseMenu::Run()
{
	while (paused == true)
	{
		this->UI_AddWindowToListenTo(pauseMenuName);

		while (HAPI_Sprites.Update() && paused) {}

		return true;
	}

	return false;
}