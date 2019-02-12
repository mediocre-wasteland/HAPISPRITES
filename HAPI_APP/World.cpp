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

	if (!LoadSprites())
	{
		HAPI_Sprites.UserMessage("Failed to Load Sprites", "ERROR", HAPI_ButtonType::eButtonTypeOk);
		return false;
	}

	if (!LoadEntities()) 
	{
		HAPI_Sprites.UserMessage("Failed to Load Entities", "ERROR", HAPI_ButtonType::eButtonTypeOk);
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
	sprite->GetSurface()->MakeAlphaChannelFromColourKey(Colour255::BLACK);

	sprite->SetAutoAnimate(5);

	sprite2->SetAutoAnimate(20, true, "Right");

	while (HAPI_Sprites.Update())
	{
		Update();
	}

	return false;
}


//Private
bool World::LoadSprites()
{
	sprite = HAPI_Sprites.MakeSprite("Data\\helicopter.png", 4);

	sprite2 = HAPI_Sprites.LoadSprite("Data\\Troll2.xml");

	if (!sprite2)
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
		return false;
	}

	return true;
}

bool World::LoadEntities()
{
	return true;
}

bool World::LoadWorld()
{
	return true;
}

void World::Update()
{
	SCREEN_SURFACE->Clear();

	GetInput();
	CheckCollision();

	sprite->GetTransformComp().SetPosition({ 500, 200 });
	sprite->GetTransformComp().SetScaling({ 2.0f, 2.0f });
	sprite->GetTransformComp().SetRotation(0.3f);


	Render();
}

void World::Render()
{
	sprite->Render(SCREEN_SURFACE);
	sprite2->Render(SCREEN_SURFACE);

}

void World::GetInput()
{
	const HAPISPACE::KeyboardData &keyboardInput = HAPI_Sprites.GetKeyboardData();

	if (keyboardInput.scanCode['D'] || keyboardInput.scanCode[HK_RIGHT])
	{
		//Move Right
	}
	
	if (keyboardInput.scanCode['A'] || keyboardInput.scanCode[HK_LEFT])
	{
		//Move Left
	}

	if (keyboardInput.scanCode['W'] || keyboardInput.scanCode[HK_SPACE])
	{
		//Jump
	}
}

bool World::CheckCollision()
{
	return false;
}
