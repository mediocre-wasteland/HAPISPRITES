#pragma once

#include "Collectables.h"
#include "PlayerEntity.h"
#include "Map.h"

class AmmoCollectable : public Collectables
{
public:
	AmmoCollectable(std::string &fileName);
	~AmmoCollectable();

	void Update(PlayerEntity* player, Map& gameMap) override;

private:
	int mAmount{ 12 }; // the amount of ammo this collectable will grant if collided with

};

