#include "KeyCollectable.h"

KeyCollectable::KeyCollectable(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::eCollectable;

	SetPosition({ 250 , 550 });
}

KeyCollectable::~KeyCollectable()
{

}

void KeyCollectable::Update()
{
	HAPISPACE::VectorF position({ GetPosition() });

	if (isColliding == true)
	{
		std::cout << "KEY" << std::endl;
	}
	isColliding = false;
	sprite->GetTransformComp().SetPosition(position);
}