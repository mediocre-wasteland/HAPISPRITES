#include "KeyCollectable.h"

KeyCollectable::KeyCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
}

KeyCollectable::~KeyCollectable()
{

}

bool KeyCollectable::Update(PlayerEntity* player, Map& gameMap)
{
	//Check if the player has collided with the key and remove the key
	if (isColliding == true)
	{
		player->mHasKey = true;
		mAlive = false;
	}

	isColliding = false;

	return true;
}