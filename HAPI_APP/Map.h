#pragma once

#include <HAPISprites_Lib.h>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "Entity.h"
#include "BackGroundEntity.h"
#include "ObstacleEntity.h"
#include "KeyCollectable.h"
#include  "AmmoCollectable.h"
#include "MoneyCollectable.h"

enum eColType
{
	Key,
	Ammo,
	Money
};

class Map
{
public:
	Map();
	~Map();

	bool Initialise();

	void CreateLevel();
	void Render();

	void NextLevel() { mCurrentLevel++;  CreateLevel(); }
	void MoveMap(eDirection moveDirection);

	std::unordered_map <std::string, Entity*> GetObstacles() { return mObstacleMap; }
	std::unordered_map <std::string, Entity*> GetCollectables() { return mCollectableMap; }


private:
	int mCurrentLevel = 1;

	std::unordered_map <std::string, Entity*> mBackgroundMap;
	std::unordered_map <std::string, Entity*> mCollectableMap;
	std::unordered_map <std::string, Entity*> mObstacleMap;

	void AddBackground(std::string fileName, float x, float y);
	void AddCollectable(std::string fileName, float x, float y, eColType type);
	void AddObstacle(std::string fileName, float x, float y);

};

