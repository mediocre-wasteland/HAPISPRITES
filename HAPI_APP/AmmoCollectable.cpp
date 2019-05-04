#include "AmmoCollectable.h"

AmmoCollectable::AmmoCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
}

AmmoCollectable::~AmmoCollectable()
{
}

bool AmmoCollectable::Update(PlayerEntity* player, Map& gameMap)
{
	//Check if colliding, add ammo and set ammo to no longer be alive
	if (isColliding == true)
	{
		player->AddLGAmmo(mAmount);
		mAlive = false;
	}

	isColliding = false;

	return true;
}