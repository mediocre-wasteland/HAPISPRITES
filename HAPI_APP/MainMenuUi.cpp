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

	// Open the main menu
	UI.OpenWindow(mainMenuName, false, true, mainMenuName, EDirection::eNorth, true,EGap::eLoose, {45,0});

	//Register Button Clicks
	this->UI_AddWindowToListenTo(mainMenuName); 

	Play();

	return true;
}

void MainMenuUi::Update()
{
	//Clear to Aqua Colour
	SCREEN_SURFACE->Clear(HAPISPACE::Colour255(12, 223, 235));
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
	//Main Menu Buttons
	if (buttonName == "CreditsButton")
	{
		UI.CloseWindow(mainMenuName);
		UI.OpenWindow(creditsMenuName, false, true, creditsMenuName, EDirection::eNorth, true, EGap::eLoose, { 45,0 });
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

	//Options Menu Buttons
	if (buttonName == "ReturnButtonOptionsMenu")
	{
		UI.CloseWindow(optionsMenuName);
		UI.OpenWindow(mainMenuName, false, true, mainMenuName, EDirection::eNorth, true, EGap::eLoose, { 45,0 });
		this->UI_AddWindowToListenTo(mainMenuName);
	}

	//Credits Menu Buttons
	if (buttonName == "ReturnCreditsMenu")
	{
		UI.CloseWindow(creditsMenuName);
		UI.OpenWindow(mainMenuName, false, true, mainMenuName, EDirection::eNorth, true, EGap::eLoose, { 45,0 });
		this->UI_AddWindowToListenTo(mainMenuName);
	}
}

//Check for key presses while on menu screens
void MainMenuUi::OnKeyEvent(EKeyEvent keyEvent, BYTE keyCode)
{
	if (keyEvent == EKeyEvent::ePress)
	{
		switch (keyCode)
		{
		case '1':
			//Play game
			if (isMainMenu == true)
			{
				UI.GetWindow(mainMenuName, true)->SimulateButtonPress("PlayButton", true);
				isMainMenu = false;
				isOptionsMenu = false;
				isCreditsMenu = false;
			}

			//Return to main menu
			if (isOptionsMenu == true)
			{
				UI.GetWindow(optionsMenuName, true)->SimulateButtonPress("ReturnButtonOptionsMenu", true);
				isMainMenu = true; // Set to use Main Menu Controls to True
				isOptionsMenu = false; // Set to not use Options Menu Controls
			}

			//Return to main menu
			if (isCreditsMenu == true)
			{
				UI.GetWindow(creditsMenuName, true)->SimulateButtonPress("ReturnCreditsMenu");
				isMainMenu = true;
				isCreditsMenu = false;
			}
			break;

		case '2':
			//Open options menu
			if (isMainMenu == true)
			{
				UI.GetWindow(mainMenuName, true)->SimulateButtonPress("OptionsButton", true);
				isMainMenu = false;
				isOptionsMenu = true;

			}
			break;

		case '3':
			//Open credits menu
			if (isMainMenu == true)
			{
				UI.GetWindow(mainMenuName, true)->SimulateButtonPress("CreditsButton", true);
				isMainMenu = false;
				isCreditsMenu = true;
			}
			break;

		case '4':
			//Exit game
			if (isMainMenu == true)
			{
				UI.GetWindow(mainMenuName, true)->SimulateButtonPress("ExitButton", true);
			}
			break;
		}
	}
}