#pragma once

#include <HAPISprites_Lib.h>
#include "Entity.h"
#include "PlayerEntity.h"
#include "Map.h"

class DoorEntity : public Collectables
{
public:
	DoorEntity(std::string &fileName);
	~DoorEntity();

	bool Update(PlayerEntity* player, Map& gameMap);
};