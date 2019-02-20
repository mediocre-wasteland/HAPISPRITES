#pragma once

#include <HAPISprites_Lib.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Entity.h"
#include "BackGroundEntity.h"
#include "ObstacleEntity.h"

class Map
{
public:
	Map();
	~Map();

	bool Initialise();

	void CreateLevel();
	void Render();

	void NextLevel() { currentLevel++;  CreateLevel(); }
	void MoveMap(eDirection moveDirection);


private:
	int currentLevel = 1;
	std::unordered_map <std::string, Entity*> entityMap;
};

