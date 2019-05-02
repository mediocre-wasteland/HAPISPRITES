#include "MoneyCollectable.h"



MoneyCollectable::MoneyCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCradle;
}


MoneyCollectable::~MoneyCollectable()
{
}

bool MoneyCollectable::Update(PlayerEntity* player, Map& gameMap) // updates every gameloop needs the pointer to the player to affect it
{
	if (isColliding == true) // checks whether the collectable is colliding
	{
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Baby.wav");
		std::cout << "Baby Collision" << std::endl;
		player->AddMoney(mValue);// increases the mMoneyAmount variable in PlayerEntity by the mValue amount of this class  
		mAlive = false;
	}

	isColliding = false; // resets the collision status of the object at the end of update

	return true;
}