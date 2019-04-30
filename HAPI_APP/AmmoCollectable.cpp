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
	if (isColliding == true)// checks whether the collectable is colliding
	{
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//KeyPickup.wav");
		std::cout << "Ammo Collision" << std::endl;
		player->AddLGAmmo(mAmount);
		mAlive = false;
	}

	isColliding = false; // resets the collision status of the object at the end of update

	return true;
}