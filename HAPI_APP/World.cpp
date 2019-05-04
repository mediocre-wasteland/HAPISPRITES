#include "World.h"


World::World()
{
}


World::~World()
{
	for (auto p : mEntityMap)
	{
		delete p.second;
	}

	delete backgroundImage;
}

bool World::LoadSounds()
{
	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//LoveGunEffect.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load LOVEGUNEFFECT.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Baby.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load Baby.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//LoveGun.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load LoveGun.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//KeyPickup.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load KeyPickup.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Jump.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load Jump.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Clapping.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load Clapping.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}
	
	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Running//run.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load run.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Running//run1.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load run1.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Running//run2.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load run2.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Running//run3.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load run3.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Running//run4.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load run4.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Running//run5.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load run5.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}
	
	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Running//run6.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load run6.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//Running//run7.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load run7.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	return true;
}

bool World::Initialise()
{
	//Initialise HAPI with set window size
	if (!HAPI_Sprites.Initialise(screenDimensions.x, screenDimensions.y, "Mediocre Wasteland Game Jam", eHSEnableUI))
	{
		HAPI_Sprites.UserMessage("Failed to Initialise", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!LoadEntities())
	{
		HAPI_Sprites.UserMessage("Failed to Load Entities", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!LoadSprites())
	{
		HAPI_Sprites.UserMessage("Failed to Load Sprites", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}
	
	if (!LoadSounds())
	{
		HAPI_Sprites.UserMessage("Failed to Load Sounds", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	options.loop = true;
	options.volume = 0.5;

	HAPI_Sprites.PlayStreamedMedia((std::string)"Data\\Sounds\\Waves.wav", options, instanceID, 0.0f);

	if (!LoadWorld())
	{
		HAPI_Sprites.UserMessage("Failed to Load World", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	HAPI_Sprites.SetShowFPS(true);

	MainMenuUi mainmenu;
	mainmenu.Initialise(&mGameMap);

	//Stay on main menu until play or exit is pressed.
	if (mainmenu.GetPlay())
	{
		if (!Play())
		{
			return false;
		}
	}

	return true;
}

bool World::Play()
{
	//Enter game update loop
	while (HAPI_Sprites.Update())
	{
		Update();
	}

	return false;
}

bool World::LoadSprites()
{
	if (!mEntityMap.at("Player")->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
		return false;
	}

	//Load multiple bullets
	for (int i{ 0 }; i < 10; i++)
	{
		std::string name = "Bullet" + std::to_string(i);

		if (!mEntityMap.at((name))->LoadSprite())
		{
			HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
			return false;
		}
	}

	backgroundImage->LoadSprite();

	return true;
}

//Load all information needed for entities
bool World::LoadEntities()
{
	mEntityMap["Player"] = new PlayerEntity((std::string)"Data\\Sprites\\Player.xml");

	for (int i = 0; i < 10; i++)
	{
		std::string name = "Bullet" + std::to_string(i);
		mEntityMap[name] = new BulletEntity((std::string)"Data\\BulletPlaceholder.xml");
	}

	backgroundImage = new BackGroundEntity((std::string) "Data\\Sprites\\BG.xml");

	return true;
}

bool World::LoadWorld()
{
	mGameMap.Initialise();
	mGameMap.CreateLevel();

	return true;
}

void World::Update()
{	
	//World tick timer to reduce amount of updates/checks
	if (HAPI_Sprites.GetTime() - timeSinceLastWorldTick >= worldTickTime)
	{
		CheckCollision();
		UpdateCamera();

		//Clear and repopulate the bulelt vector
		((PlayerEntity*)mEntityMap.at("Player"))->BulletVectorClear();

		for (int i = 0; i < 10; i++)
		{
			std::string name = "Bullet" + std::to_string(i);
			((PlayerEntity*)mEntityMap.at("Player"))->BulletVectorPushBack((BulletEntity*)mEntityMap.at(name));
		}

		//Update the entity status
		for (auto &p : mEntityMap)
		{
			p.second->Update();
		}

		//Update the collectable status
		for (auto &p : mGameMap.GetCollectables())
		{
			bool Done = ((Collectables*)p.second)->Update((PlayerEntity*)mEntityMap.at("Player"), mGameMap);

			if (!Done)
			{
				break;
			}
		}

		const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

		//Enter into pause menu when Esc is pressed
		if (mKeyboardInput.scanCode[HK_ESCAPE])
		{
			PauseMenu pausemenu;
			pausemenu.Initialise();
		}

		//Set to new level when goal is reached
		if (currentLevel != mGameMap.GetLevel())
		{
			mEntityMap["Player"]->GetSprite()->GetTransformComp().SetPosition(mGameMap.GetSpawnPos());
			mEntityMap["Player"]->isTravellingUp = false;
			((PlayerEntity*)mEntityMap["Player"])->mHasKey = false;
			currentLevel = mGameMap.GetLevel();
			mGameCamera.ResetCamera(mGameMap, mEntityMap);
		}

		timeSinceLastWorldTick = HAPI_Sprites.GetTime();
	}

	Render();
}


void World::Render()
{
	//Clear to colour
	SCREEN_SURFACE->Clear(HAPISPACE::Colour255(12, 223, 235));

	//Render all items to the screen
	backgroundImage->Render();

	mGameMap.Render();

	for (auto &p : mEntityMap)
	{
		p.second->Render();
	}
}

void World::CheckCollision()
{
	//Check for collisions between all entities, collectables and obstacles.
	for (auto &p : mEntityMap)
	{
		p.second->CheckCollision(mGameMap.GetCollectables());
		p.second->CheckCollision(mEntityMap);
		p.second->CheckCollision(mGameMap.GetObstacles());
	}
}

void World::UpdateCamera()
{
	//Change camera position depending on player movement
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	if (mEntityMap["Player"]->GetSprite()->GetTransformComp().GetPosition().x < 512 )
	{
		mGameCamera.MoveCamera(eDirection::eRight, mGameMap, mEntityMap);	
	}
	if (mEntityMap["Player"]->GetSprite()->GetTransformComp().GetPosition().y > 704)
	{
		mGameCamera.MoveCamera(eDirection::eUp, mGameMap, mEntityMap);
	}
	if (mEntityMap["Player"]->GetSprite()->GetTransformComp().GetPosition().y < 128)
	{
		mGameCamera.MoveCamera(eDirection::eDown, mGameMap, mEntityMap);
	}
	if (mEntityMap["Player"]->GetSprite()->GetTransformComp().GetPosition().x > 768)
	{
		mGameCamera.MoveCamera(eDirection::eLeft, mGameMap, mEntityMap);
	}
}