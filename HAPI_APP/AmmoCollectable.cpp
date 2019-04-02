#include "AmmoCollectable.h"



AmmoCollectable::AmmoCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
}


AmmoCollectable::~AmmoCollectable()
{
}

void AmmoCollectable::Update(PlayerEntity* player, Map& gameMap)
{
	if (isColliding == true)// checks whether the collectable is colliding
	{
		std::cout << "Ammo Collision" << std::endl;
		player->AddLGAmmo(mAmount);
		mAlive = false;
	}

	isColliding = false; // resets the collision status of the object at the end of update
}