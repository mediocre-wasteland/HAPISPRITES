#include "MoneyCollectable.h"

MoneyCollectable::MoneyCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCradle;
}

MoneyCollectable::~MoneyCollectable()
{
}

//NOTE: MONEY IS NOW SHOWN AS BABIES IN GAME
bool MoneyCollectable::Update(PlayerEntity* player, Map& gameMap)
{
	//Check if the bullet has collided with a baby and increase the score
	if (isColliding == true)
	{
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Baby.wav");
		player->AddMoney(mValue);
		mAlive = false;
	}

	isColliding = false;

	return true;
}