#include "BulletEntity.h"

BulletEntity::BulletEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = false;
	mSide = eSide::eBullet;
}

BulletEntity::~BulletEntity()
{
}

void BulletEntity::Update()
{
	if (!mAlive)
	{
		sprite->GetTransformComp().SetPosition(VectorF(-10.f, -10.f));
		return;
	}

	//Check if bullet should move left or right and move int that direction
	switch (mDirection)
	{
	case(eDirection::eRight):
		sprite->GetTransformComp().SetPosition({ sprite->GetTransformComp().GetPosition().x + mSpeed,sprite->GetTransformComp().GetPosition().y });
		break;
	case(eDirection::eLeft):
		sprite->GetTransformComp().SetPosition({ sprite->GetTransformComp().GetPosition().x - mSpeed, sprite->GetTransformComp().GetPosition().y });
		break;
	default:
		std::cerr << "Bullet direction not left or right" << std::endl;
		break;
	}

	//Set bullet to dead if it has collided
	if (isColliding)
	{
		mAlive = false;
		isColliding = false;
	}
}