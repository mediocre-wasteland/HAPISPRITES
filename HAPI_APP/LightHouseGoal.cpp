#include "LightHouseGoal.h"



LightHouseGoal::LightHouseGoal(std::string &fileName) : Collectables(fileName)
{
	mAlive = true;
	mSide = eSide::eCollectable;
	SetPosition({ 150 , 450 }); //position of object on screen
}


LightHouseGoal::~LightHouseGoal()
{
}

void LightHouseGoal::Update(PlayerEntity* player, Map& gameMap)
{
	if (isColliding == true)
	{
		gameMap.NextLevel();
	}

	isColliding = false;
}