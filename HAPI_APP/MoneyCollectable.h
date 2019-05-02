#pragma once

#include "Collectables.h"
#include "PlayerEntity.h"
#include "Map.h"

class MoneyCollectable : public Collectables
{
public:
	MoneyCollectable(std::string &fileName);
	~MoneyCollectable();
	bool Update(PlayerEntity* player, Map& gameMap) override;// main update used to check if the collectable is collected

private:
	int mValue{ 1 }; // the amount of money this will grant if collided with
};

