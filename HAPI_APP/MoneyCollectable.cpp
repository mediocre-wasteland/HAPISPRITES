#include "MoneyCollectable.h"



MoneyCollectable::MoneyCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
	SetPosition({ 250 , 450 }); //position of object on screen
}


MoneyCollectable::~MoneyCollectable()
{
}

void MoneyCollectable::Update(PlayerEntity* player) // updates every gameloop needs the pointer to the player to affect it
{
	if (isColliding == true) // checks whether the collectable is colliding
	{
		player->AddMoney(mValue);// increases the mMoneyAmount variable in PlayerEntity by the mValue amount of this class  
		mAlive = false;
	}

	isColliding = false; // resets the collision status of the object at the end of update
}