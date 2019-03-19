#include "AmmoCollectable.h"



AmmoCollectable::AmmoCollectable(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::eCollectable;
	SetPosition({ 150 , 450 });
}


AmmoCollectable::~AmmoCollectable()
{
}

void AmmoCollectable::Update(PlayerEntity* player)
{
	HAPISPACE::VectorF position({ GetPosition() });

	if (isColliding == true)
	{
		player->AddLGAmmo(mAmount);

	}
	std::cout << player->GetAmmoAmount() << std::endl;

	sprite->GetTransformComp().SetPosition(position);
	isColliding = false;
}