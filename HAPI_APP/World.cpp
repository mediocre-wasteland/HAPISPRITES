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
	//sprite->GetSurface()->MakeAlphaChannelFromColourKey(Colour255::BLACK);

	//sprite->SetAutoAnimate(5);

	//sprite2->SetAutoAnimate(20, true, "Right");

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
	gameMap.CreateLevel(1);

	return true;
}

void World::Update()
{
	SCREEN_SURFACE->Clear();

	entityMap.at("Player")->Update();
	entityMap.at("Enemy")->Update();
	//GetInput();
	CheckCollision();

	entityMap.at("Player")->SetPosition({ entityMap.at("Player")->GetPosition().x, entityMap.at("Player")->GetPosition().y });
	entityMap.at("Enemy")->SetPosition({ entityMap.at("Enemy")->GetPosition().x, entityMap.at("Enemy")->GetPosition().y });
	entityMap.at("Player")->SetScaling( 1.0f, 1.0f );
	entityMap.at("Player")->SetRotation(0.3f);


	Render();
}

void World::Render()
{
	gameMap.Render();
	entityMap.at("Player")->Render();
	entityMap.at("Enemy")->Render();
}

bool World::CheckCollision()
{
	return false;
}
