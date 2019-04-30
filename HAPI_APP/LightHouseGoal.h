#pragma once

#include "Collectables.h"
#include "PlayerEntity.h"
#include "Map.h"

class LightHouseGoal : public Collectables
{
public:
	LightHouseGoal(std::string &fileName);
	~LightHouseGoal();

	bool Update(PlayerEntity* player, Map& gameMap) override;
};

