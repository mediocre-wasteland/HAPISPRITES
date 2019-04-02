#pragma once

#include <HAPISprites_Lib.h>
#include "PlayerEntity.h"

class Map;

using namespace HAPISPACE;

class Collectables : public Entity
{
public:
	Collectables(std::string &fileName);
	~Collectables();

	void Update() override final { }// not used

	virtual void Update(PlayerEntity* player, Map& gameMap) = 0;// main update used to check if the collectable is collected

	eSide GetSide() const override final { return eSide::eCollectable; };
	eDirection GetDirection() const override final { return mDirection; };

};

