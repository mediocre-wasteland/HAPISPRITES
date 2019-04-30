#pragma once

#include <HAPISprites_Lib.h>
#include "PlayerEntity.h"

class Map;

using namespace HAPISPACE;

class Collectables : public Entity
{
public:
	Collectables(std::string &fileName);
	virtual ~Collectables();

	void Update() override final { }// not used

	virtual bool Update(PlayerEntity* player, Map& gameMap) = 0;// main update used to check if the collectable is collected

	eSide GetSide() const override final { return mSide; };
	eDirection GetDirection() const override final { return mDirection; };

};

