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
	//Check if the player has a key and set the door to open if they do
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