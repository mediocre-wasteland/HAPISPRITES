#include "MoneyCollectable.h"



MoneyCollectable::MoneyCollectable(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::eCollectable;
	SetPosition({ 250 , 450 });
}


MoneyCollectable::~MoneyCollectable()
{
}

void MoneyCollectable::Update(PlayerEntity* player)
{
	HAPISPACE::VectorF position({ GetPosition() });

	if (isColliding == true)
	{
		player->AddMoney(mValue);

	}
	std::cout << player->GetMoneyAmount() << std::endl;

	sprite->GetTransformComp().SetPosition(position);
	isColliding = false;
}