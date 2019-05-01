#include "MainMenuUi.h"

MainMenuUi::MainMenuUi()
{

}
MainMenuUi::~MainMenuUi()
{

}
bool MainMenuUi::Initialise(Map* gameMap)
{
	mapMainMenu = gameMap;

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

	UI.OpenWindow(mainMenuName,false,true,mainMenuName,EDirection::eNorth,true,EGap::eLoose,{45,0}); 	// Open the main menu

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
	while (HAPI_Sprites.Update() && !play)
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
		UI.OpenWindow(creditsMenuName,false, true, creditsMenuName, EDirection::eNorth, true, EGap::eLoose, { 45,0 });
		this->UI_AddWindowToListenTo(creditsMenuName);
	}

	if (buttonName == "ExitButton")
	{
		HAPI_Sprites.Close();
	}

	if (buttonName == "OptionsButton")
	{
		UI.CloseWindow(mainMenuName);
		UI.OpenWindow(optionsMenuName, false, true, optionsMenuName, EDirection::eNorth, true, EGap::eLoose, { 45,0 });
		this->UI_AddWindowToListenTo(optionsMenuName);
	}
	if (buttonName == "PlayButton")
	{
		play = true;
		mapMainMenu->NextLevel();
		UI.CloseWindow(mainMenuName);
	}
	/*
	*Options Menu
	*Buttons
	*/
	if (buttonName == "ReturnButtonOptionsMenu")
	{
		UI.CloseWindow(optionsMenuName);
		UI.OpenWindow(mainMenuName, false, true, mainMenuName, EDirection::eNorth, true, EGap::eLoose, { 45,0 });
		this->UI_AddWindowToListenTo(mainMenuName);
	}
	/*
	*Credits Menu
	*Buttons
	*/
	if (buttonName == "ReturnCreditsMenu")
	{
		UI.CloseWindow(creditsMenuName);
		UI.OpenWindow(mainMenuName, false, true, mainMenuName, EDirection::eNorth, true, EGap::eLoose, { 45,0 });
		this->UI_AddWindowToListenTo(mainMenuName);
	}
}

void MainMenuUi::OnKeyEvent(EKeyEvent keyEvent, BYTE keyCode)
{
	if (keyEvent == EKeyEvent::ePress)
	{
		switch (keyCode)
		{
		case '1':
			if (isMainMenu == true) // Main Menu & True by Default
			{
				UI.GetWindow(mainMenuName, true)->SimulateButtonPress("PlayButton", true);
				isMainMenu = false;
				isOptionsMenu = false;
				isCreditsMenu = false;
			}
			if (isOptionsMenu == true) // Options Menu
			{
				UI.GetWindow(optionsMenuName, true)->SimulateButtonPress("ReturnButtonOptionsMenu", true);
				isMainMenu = true; // Set to use Main Menu Controls to True
				isOptionsMenu = false; // Set to not use Options Menu Controls
			}
			if (isCreditsMenu == true)
			{
				UI.GetWindow(creditsMenuName, true)->SimulateButtonPress("ReturnCreditsMenu");
				isMainMenu = true;
				isCreditsMenu = false;

			}
			break;
		case '2':
			if (isMainMenu == true) // Main Menu
			{
				UI.GetWindow(mainMenuName, true)->SimulateButtonPress("OptionsButton", true);
				isMainMenu = false;
				isOptionsMenu = true;

			}
			break;
		case '3':
			if (isMainMenu == true) // Main Menu
			{
				UI.GetWindow(mainMenuName, true)->SimulateButtonPress("CreditsButton", true);
				isMainMenu = false;
				isCreditsMenu = true;
			}
			break;
		case '4':
			if (isMainMenu == true) // Main Menu
			{
				UI.GetWindow(mainMenuName, true)->SimulateButtonPress("ExitButton", true);
			}
			break;
		}
	}
}