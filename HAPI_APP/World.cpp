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

//Public
bool World::LoadSounds()
{
	//loads sounds 
	//may not actually need this as sounds seem to load on play
	if (!HAPI_Sprites.LoadSound((std::string)"Data//Sounds//LoveGunEffect.wav"))
	{
		HAPI_Sprites.UserMessage("Could not load LOVEGUNEFFECT.wav", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}
	return true;
}

bool World::Initialise()
{

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
	while (HAPI_Sprites.Update())
	{
		Update();
	}

	return false;
}


//Private
bool World::LoadSprites()
{
	if (!mEntityMap.at("Player")->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
		return false;
	}

	if (!mEntityMap.at("Enemy")->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
		return false;
	}

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

bool World::LoadEntities()
{
	mEntityMap["Player"] = new PlayerEntity((std::string)"Data\\Sprites\\Player.xml");
	mEntityMap["Enemy"] = new EnemyEntity((std::string) "Data\\Troll2.xml");

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
	if (HAPI_Sprites.GetTime() - timeSinceLastWorldTick >= worldTickTime)
	{
		CheckCollision();
		UpdateCamera();

		// TEMPORARY CODE: Supplying PlayerPos To The Entity
		mEntityMap.at("Enemy")->GetPlayerPosFromWorld(mEntityMap.at("Player")->GetOldPosition());

		mEnemies.clear();
		mEnemies.push_back((EnemyEntity*)mEntityMap.at("Enemy"));
		((PlayerEntity*)mEntityMap.at("Player"))->BulletVectorClear();

		for (int i = 0; i < 10; i++)
		{
			std::string name = "Bullet" + std::to_string(i);
			((PlayerEntity*)mEntityMap.at("Player"))->BulletVectorPushBack((BulletEntity*)mEntityMap.at(name));
			((BulletEntity*)mEntityMap.at(name))->Update(mEnemies);
		}

		mEntityMap.at("Enemy")->SetScaling(0.5f, 0.5f);

		for (auto &p : mEntityMap)
		{
			p.second->Update();
		}

		for (auto &p : mGameMap.GetCollectables())
		{
			bool Done = ((Collectables*)p.second)->Update((PlayerEntity*)mEntityMap.at("Player"), mGameMap);

			if (!Done)
			{
				break;
			}
		}

		const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

		if (mKeyboardInput.scanCode[HK_ESCAPE])
		{
			PauseMenu pausemenu;
			pausemenu.Initialise();
		}

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
	SCREEN_SURFACE->Clear(HAPISPACE::Colour255(12, 223, 235));

	backgroundImage->Render();

	mGameMap.Render();

	for (auto &p : mEntityMap)
	{
		p.second->Render();
	}

}

void World::CheckCollision()
{
	for (auto &p : mEntityMap)
	{
		p.second->CheckCollision(mGameMap.GetCollectables());
		p.second->CheckCollision(mEntityMap);
		p.second->CheckCollision(mGameMap.GetObstacles());
	}
}

void World::UpdateCamera()
{
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