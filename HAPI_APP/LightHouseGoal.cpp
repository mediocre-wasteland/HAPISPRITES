#include "LightHouseGoal.h"



LightHouseGoal::LightHouseGoal(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
}


LightHouseGoal::~LightHouseGoal()
{
}

void LightHouseGoal::Update(PlayerEntity* player, Map& gameMap)
{
	if (isColliding == true)
	{
		std::cout << "Lighthouse Collision" << std::endl;
		gameMap.NextLevel();
	}

	isColliding = false;
}