#include "KeyCollectable.h"

KeyCollectable::KeyCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
}

KeyCollectable::~KeyCollectable()
{

}

void KeyCollectable::Update(PlayerEntity* player, Map& gameMap)
{
	if (isColliding == true)
	{
		std::cout << "Key Collision" << std::endl;
		player->mHasKey = true;
		mAlive = false;
	}

	isColliding = false;
}