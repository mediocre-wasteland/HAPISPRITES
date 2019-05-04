#pragma once

#include "Collectables.h"
#include "PlayerEntity.h"
#include "Map.h"

//NOTE: MONEY IS NOW SHOWN AS BABIES IN GAME
class MoneyCollectable : public Collectables
{
public:
	MoneyCollectable(std::string &fileName);
	~MoneyCollectable();
	bool Update(PlayerEntity* player, Map& gameMap) override;

private:
	int mValue{ 1 };
};