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
	//sprite2->SetAutoAnimate(20, true, "Right"); // Animate Character Walk Right at 20 FPS and loop

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

	return true;
}

bool World::LoadEntities()
{
	entityMap["Player"] = new PlayerEntity((std::string)"Data\\stickGuy.xml");
	entityMap["Enemy"] = new EnemyEntity((std::string) "Data\\Troll2.xml");
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
	SCREEN_SURFACE->Clear();

	entityMap.at("Player")->Update();
	entityMap.at("Enemy")->Update();
	CheckCollision();

	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	if (mKeyboardInput.scanCode['L'])
	{
		levelComplete = true;
	}

	if (levelComplete)
	{
		gameMap.NextLevel();
		levelComplete = false;
	}

	Render();
}

void World::Render()
{
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
}
