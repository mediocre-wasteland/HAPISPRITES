#include "KeyCollectable.h"

KeyCollectable::KeyCollectable(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::eCollectable;
}

KeyCollectable::~KeyCollectable()
{

}

void KeyCollectable::Update()
{
	HAPISPACE::VectorF position({ GetPosition() });

	SetPosition({ 250 , 550});

	if (isColliding == true)
	{
		std::cout << "KEY" << std::endl;
	}

	sprite->GetTransformComp().SetPosition(position);
}