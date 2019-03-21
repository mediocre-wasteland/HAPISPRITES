#include "KeyCollectable.h"

KeyCollectable::KeyCollectable(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;

	SetPosition({ 250 , 550 });
}

KeyCollectable::~KeyCollectable()
{

}

void KeyCollectable::Update(PlayerEntity* player)
{
	if (isColliding == true)
	{
		player->mHasKey = true;
		mAlive = false;
	}
	isColliding = false;
}