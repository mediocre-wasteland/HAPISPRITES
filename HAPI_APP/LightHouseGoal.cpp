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
	//Check if the player has completed the level
	if (isColliding == true)
	{
		//Check if player has finished the game and display a message
		if (gameMap.GetLevel() == 5)
		{
			int finalScore = player->GetMoneyAmount(); 
			HAPI_Sprites.UserMessage("Well Done You Won! You Collected "  + std::to_string(finalScore) + " babies out of 15", "Winner");
			gameMap.KillLevel();
			exit(0);
		}

		//Move to the next level
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Clapping.wav");
		gameMap.NextLevel();
		player->mHasKey = false;
		return false;
	}

	isColliding = false;

	return true;
}