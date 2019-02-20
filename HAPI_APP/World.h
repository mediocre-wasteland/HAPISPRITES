#pragma once

#include <HAPISprites_Lib.h>
#include "HAPI_SPRITES/Shapes/Vector.h"
#include <unordered_map>
#include "Entity.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "Map.h"

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
	std::unordered_map <std::string, Entity*> entityMap;
	Map gameMap;
	bool levelComplete = false;


	bool LoadSprites();
	bool LoadEntities();
	bool LoadWorld();

	void Update();
	void Render();

	bool CheckCollision();
};

