#include "DoorEntity.h"



DoorEntity::DoorEntity(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eObstacle;
}


DoorEntity::~DoorEntity()
{
}

bool DoorEntity::Update(PlayerEntity * player, Map & gameMap)
{
	if (player->mHasKey)
	{
		mSide = eSide::eNeutral;
		sprite->SetAutoAnimate(2, false, "Open");
	}
	else
	{
		mSide = eSide::eObstacle;
		sprite->SetAutoAnimate(2, false, "Closed");
	}

	return true;
}

