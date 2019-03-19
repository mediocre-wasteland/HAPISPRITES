#include "MoneyCollectable.h"



MoneyCollectable::MoneyCollectable(std::string &filename) : Entity(filename)
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
	HAPISPACE::VectorF position({ GetPosition() });

	if (isColliding == true) // checks whether the collectable is colliding
	{
		player->AddMoney(mValue);// increases the mMoneyAmount variable in PlayerEntity by the mValue amount of this class  

	}
	std::cout << player->GetMoneyAmount() << std::endl;// returns to console players current money DEBUG FUNCTION

	sprite->GetTransformComp().SetPosition(position); // sets position on screen
	isColliding = false; // resets the collision status of the object at the end of update
}