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

	void CreateLevel(int levelNum);

	void Render();


private:

	std::unordered_map <std::string, Entity*> entityMap;
};

