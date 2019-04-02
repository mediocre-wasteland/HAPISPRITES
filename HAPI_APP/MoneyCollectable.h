#pragma once

#include "Collectables.h"
#include "PlayerEntity.h"
#include "Map.h"

class MoneyCollectable : public Collectables
{
public:
	MoneyCollectable(std::string &fileName);
	~MoneyCollectable();
	void Update(PlayerEntity* player, Map& gameMap) override;// main update used to check if the collectable is collected

private:
	int mValue{ 250 }; // the amount of money this will grant if collided with
};

