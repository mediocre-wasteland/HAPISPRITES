#pragma once

#include <HAPISprites_Lib.h>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "Entity.h"
#include "BackGroundEntity.h"
#include "ObstacleEntity.h"
#include "KeyCollectable.h"
#include "AmmoCollectable.h"
#include "MoneyCollectable.h"
#include "LightHouseGoal.h"
#include "DoorEntity.h"

enum eColType
{
	Key,
	Ammo,
	Money,
	Lighthouse,
	Door
};

enum eOrientation
{
	Horizontal,
	Vertical
};

class Map
{
public:
	Map();
	~Map();

	bool Initialise();

	void CreateLevel();
	void Render();

	int GetHeight() { return mLevelHeight; };
	int GetWidth() { return mLevelWidth; };
	int GetLevel() { return mCurrentLevel; }
	HAPISPACE::VectorF GetSpawnPos() { return spawnPos; }
	eOrientation GetOrientation();

	void NextLevel() { mCurrentLevel++;  CreateLevel(); }
	void MoveMap(eDirection moveDirection);

	std::unordered_map <std::string, Entity*> GetObstacles() { return mObstacleMap; }
	std::unordered_map <std::string, Entity*> GetCollectables() { return mCollectableMap; }


private:
	int mCurrentLevel = 0;
	int mLevelHeight;
	int mLevelWidth;
	HAPISPACE::VectorF spawnPos { 0,0 };

	std::unordered_map <std::string, Entity*> mBackgroundMap;
	std::unordered_map <std::string, Entity*> mCollectableMap;
	std::unordered_map <std::string, Entity*> mObstacleMap;

	void AddBackground(std::string fileName, float x, float y);
	void AddCollectable(std::string fileName, float x, float y, eColType type);
	void AddObstacle(std::string fileName, float x, float y);

	void KillLevel();

};

