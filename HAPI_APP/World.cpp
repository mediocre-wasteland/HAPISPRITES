#include "World.h"

World::World()
{
}


World::~World()
{
	for (auto p : entityMap)
	{
		delete p.second;
	}
}

//Public
bool World::Initialise()
{
	if (!HAPI_Sprites.Initialise(screenDimensions.x, screenDimensions.y, "Mediocre Wasteland Game Jam"))
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

	if (!Play())
	{
		return false;
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
	if (!entityMap.at("Player")->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
		return false;
	}

	if (!entityMap.at("Enemy")->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
		return false;
	}

	if (!entityMap.at("Key")->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
		return false;
	}


	return true;
}

bool World::LoadEntities()
{
	entityMap["Player"] = new PlayerEntity((std::string)"Data\\Sprites\\Player.xml");
	entityMap["Enemy"] = new EnemyEntity((std::string) "Data\\Troll2.xml");
	entityMap["Key"] = new KeyCollectable((std::string) "Data\\KeyPlaceholder.xml");
	return true;
}

bool World::LoadWorld()
{
	gameMap.Initialise();
	gameMap.CreateLevel();

	return true;
}

void World::Update()
{	


	if (HAPI_Sprites.GetTime() - timeSinceLastWorldTick >= worldTickTime)
	{
		CheckCollision();
		UpdateCamera();

		entityMap.at("Player")->Update();
		entityMap.at("Enemy")->SetScaling(0.5f, 0.5f);
		entityMap.at("Enemy")->Update();
		entityMap.at("Key")->Update();

		const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

		if (mKeyboardInput.scanCode['P'])
		{
			levelComplete = true;
		}

		if (levelComplete)
		{
			gameMap.NextLevel();
			levelComplete = false;
		}

		timeSinceLastWorldTick = HAPI_Sprites.GetTime();
	}
	Render();
}

void World::Render()
{
	SCREEN_SURFACE->Clear(HAPISPACE::Colour255(12, 223, 235));

	gameMap.Render();

	for (auto &p : entityMap)
	{
		p.second->Render();
	}
}

void World::CheckCollision()
{
	for (auto &p : entityMap)
	{
		for (auto &s : entityMap)
		{
			p.second->CheckCollision(*s.second);
		}
	}

	for (auto &p : entityMap)
	{
		for (auto &s : gameMap.GetObstacles())
		{
			p.second->CheckCollision(*s.second);
		}
	}
	
}

void World::UpdateCamera()
{
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	if (entityMap["Player"]->GetPosition().x < 512 )
	{
		gameCamera.MoveCamera(eDirection::eRight, gameMap, entityMap);	
	}
	if (entityMap["Player"]->GetPosition().y < 832)
	{
		//gameCamera.MoveCamera(eDirection::eUp, gameMap);
	}
	if (entityMap["Player"]->GetPosition().y < 0)
	{
		//gameCamera.MoveCamera(eDirection::eDown, gameMap);
	}
	if (entityMap["Player"]->GetPosition().x > 768)
	{
		gameCamera.MoveCamera(eDirection::eLeft, gameMap, entityMap);
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