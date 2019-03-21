#include "MainMenuUi.h"

MainMenuUi::MainMenuUi()
{

}
MainMenuUi::~MainMenuUi()
{

}

bool MainMenuUi::Initialise()
{

	HAPI_Sprites.SetShowFPS(true);

	if (!Run())
	{
		return false;
	}
	return true;
}
bool MainMenuUi::Run()
{
	// Load the needed windows into HAPI
	UI.Load("Data\\UserInterface\\MainMenu.xml", mainMenuName, false);
	UI.Load("Data\\UserInterface\\CreditsMenu.xml", creditsMenuName, false);
	UI.Load("Data\\UserInterface\\OptionsMenu.xml", optionsMenuName, false);
	UI.OpenWindow(mainMenuName); 	// Open the main menu
	this->UI_AddWindowToListenTo(mainMenuName); //Register Button Clicks

	Play();
	return true;
}
void MainMenuUi::Update()
{
	SCREEN_SURFACE->Clear(HAPISPACE::Colour255(12, 223, 235));	 // Clear to Aqua Colour
}

bool MainMenuUi::Play()
{
	while (HAPI_Sprites.Update())
	{
		Update();
	}
	return true;
}

void MainMenuUi::UI_ButtonPressed(UIWindow& window, const std::string& buttonName, int* userId)
{
	/*
	*Main Menu
	*Buttons
	*/
	if (buttonName == "CreditsButton")
	{
		UI.CloseWindow(mainMenuName);
		UI.OpenWindow(creditsMenuName);
		this->UI_AddWindowToListenTo(creditsMenuName);
	}

	if (buttonName == "ExitButton")
	{
		HAPI_Sprites.Close();
	}

	if (buttonName == "OptionsButton")
	{
		UI.CloseWindow(mainMenuName);
		UI.OpenWindow(optionsMenuName);
		this->UI_AddWindowToListenTo(optionsMenuName);
	}
	if (buttonName == "PlayButton")
	{
		std::cout << "Hello World" << std::endl;
	}
	/*
	*Options Menu
	*Buttons
	*/
	if (buttonName == "ReturnButtonOptionsMenu")
	{
		UI.CloseWindow(optionsMenuName);
		UI.RefreshAllWindows();
		UI.OpenWindow(mainMenuName);
		this->UI_AddWindowToListenTo(mainMenuName);
	}
	/*
	*Credits Menu
	*Buttons
	*/
	if (buttonName == "ReturnCreditsMenu")
	{
		UI.CloseWindow(creditsMenuName);
		UI.RefreshAllWindows();
		UI.OpenWindow(mainMenuName);
		this->UI_AddWindowToListenTo(mainMenuName);
	}
}
