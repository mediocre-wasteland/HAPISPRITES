#include "AmmoCollectable.h"



AmmoCollectable::AmmoCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
	SetPosition({ 150 , 450 }); //position of object on screen
}


AmmoCollectable::~AmmoCollectable()
{
}

void AmmoCollectable::Update(PlayerEntity* player, Map& gameMap)
{
	if (isColliding == true)// checks whether the collectable is colliding
	{
		player->AddLGAmmo(mAmount);// increases the mLGAmmo variable in PlayerEntity by the mAmount amount of this class
		mAlive = false;
	}

	isColliding = false; // resets the collision status of the object at the end of update
}