#include "LightHouseGoal.h"



LightHouseGoal::LightHouseGoal(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
}


LightHouseGoal::~LightHouseGoal()
{
}

bool LightHouseGoal::Update(PlayerEntity* player, Map& gameMap)
{
	if (isColliding == true)
	{
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Clapping.wav");
		std::cout << "Lighthouse Collision" << std::endl;
		gameMap.NextLevel();
		player->mHasKey = false;
		return false;
	}

	isColliding = false;

	return true;
}