#include "AmmoCollectable.h"



AmmoCollectable::AmmoCollectable(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::eCollectable;
	SetPosition({ 150 , 450 }); //position of object on screen
}


AmmoCollectable::~AmmoCollectable()
{
}

void AmmoCollectable::Update(PlayerEntity* player)
{
	HAPISPACE::VectorF position({ GetPosition() }); // updates every gameloop needs the pointer to the player to affect it

	if (isColliding == true)// checks whether the collectable is colliding
	{
		player->AddLGAmmo(mAmount);// increases the mLGAmmo variable in PlayerEntity by the mAmount amount of this class

	}
	std::cout << player->GetAmmoAmount() << std::endl;// returns to console players current ammo DEBUG FUNCTION

	sprite->GetTransformComp().SetPosition(position); // sets position on screen
	isColliding = false; // resets the collision status of the object at the end of update
}