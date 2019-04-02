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
}

//Public
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

	return true;
}

bool World::LoadEntities()
{
	mEntityMap["Player"] = new PlayerEntity((std::string)"Data\\Sprites\\Player.xml");
	mEntityMap["Enemy"] = new EnemyEntity((std::string) "Data\\Troll2.xml");

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

		mEntityMap.at("Enemy")->SetScaling(0.5f, 0.5f);

		for (auto &p : mEntityMap)
		{
			p.second->Update();
		}

		for (auto &p : mGameMap.GetCollectables())
		{
			((Collectables*)p.second)->Update((PlayerEntity*)mEntityMap.at("Player"), mGameMap);
		}

		const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

		if (currentLevel != mGameMap.GetLevel())
		{
			mEntityMap["Player"]->GetSprite()->GetTransformComp().SetPosition(mGameMap.GetSpawnPos());
			currentLevel = mGameMap.GetLevel();
		}

		timeSinceLastWorldTick = HAPI_Sprites.GetTime();
	}

	Render();
}

void World::Render()
{
	SCREEN_SURFACE->Clear(HAPISPACE::Colour255(12, 223, 235));

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
		for (auto &s : mEntityMap)
		{
			p.second->CheckCollision(*s.second);
		}
	}

	for (auto &p : mEntityMap)
	{
		for (auto &s : mGameMap.GetObstacles())
		{
			p.second->CheckCollision(*s.second);
		}
	}
	
	for (auto &p : mGameMap.GetCollectables())
	{
		mEntityMap.at("Player")->CheckCollision(*p.second);
	}
}

void World::UpdateCamera()
{
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	if (mEntityMap["Player"]->GetSprite()->GetTransformComp().GetPosition().x < 512 )
	{
		mGameCamera.MoveCamera(eDirection::eRight, mGameMap, mEntityMap);	
	}
	if (mEntityMap["Player"]->GetSprite()->GetTransformComp().GetPosition().y < 832)
	{
		mGameCamera.MoveCamera(eDirection::eUp, mGameMap, mEntityMap);
	}
	if (mEntityMap["Player"]->GetSprite()->GetTransformComp().GetPosition().y < 0)
	{
		mGameCamera.MoveCamera(eDirection::eDown, mGameMap, mEntityMap);
	}
	if (mEntityMap["Player"]->GetSprite()->GetTransformComp().GetPosition().x > 768)
	{
		mGameCamera.MoveCamera(eDirection::eLeft, mGameMap, mEntityMap);
	}
}


///tick timer
/*
constexpr DWORD worldTickTime{ 25 };
DWORD timeSinceLastWorldTick{ 0 };

if (HAPI.GetTime() - timeSinceLastWorldTick >= worldTickTime)
{

	timeSinceLastWorldTick = HAPI.GetTime();

}
*/