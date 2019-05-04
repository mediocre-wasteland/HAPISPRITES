#pragma once

#include <HAPISprites_Lib.h>
#include "HAPI_SPRITES/Shapes/Vector.h"
#include <unordered_map>
#include "Entity.h"
#include "PlayerEntity.h"
#include "Map.h"
#include "Camera.h"
#include "KeyCollectable.h"
#include "MoneyCollectable.h"
#include "AmmoCollectable.h"
#include "MainMenuUi.h"
#include "PauseMenu.h"

using namespace HAPISPACE;

class World
{
public:
	World();
	~World();

	bool Initialise();
	bool Play();

private:

	HAPISPACE::Vector<int> screenDimensions = HAPISPACE::Vector<int>(1280, 832);

	Entity* backgroundImage;
	std::unordered_map <std::string, Entity*> mEntityMap;
	Map mGameMap;
	Camera mGameCamera {832, 1280};

	const DWORD worldTickTime{ 10 };
	DWORD timeSinceLastWorldTick{ 0 };
	HAPI_TSoundOptions options;

	int currentLevel{ 0 };
	int instanceID{ 0 };

	bool LoadSprites();
	bool LoadEntities();
	bool LoadWorld();
	bool LoadSounds();

	void Update();
	void Render();
	void CheckCollision();
	void UpdateCamera();
};