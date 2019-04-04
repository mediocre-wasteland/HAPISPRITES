#include "BulletEntity.h"



BulletEntity::BulletEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = false;
	//sprite->GetTransformComp().SetPosition(VectorF(-10.f, -10.f));
}


BulletEntity::~BulletEntity()
{
}

void BulletEntity::Update(std::vector<EnemyEntity*> enemies)
{
	if (!mAlive)
	{
		sprite->GetTransformComp().SetPosition(VectorF(-10.f, -10.f));
		return;
	}
	switch (mDirection) // this switch statement checks whether the bullet should go left or right and makes continually go that way
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

	if (sprite->GetTransformComp().GetPosition().x < 0 || sprite->GetTransformComp().GetPosition().x > mScreenSize.x || sprite->GetTransformComp().GetPosition().y < 0 || sprite->GetTransformComp().GetPosition().y > mScreenSize.y) // this deletes the bullet if it goes offscreen TODO CONSIDER HAVING THE BULLET RELEASED FROM MEMORY RATHER THAN NOT ALIVE
	{
		//mAlive = false;
		//return;
	}

	//if (isColliding)
	//{
	//	for (int i = 0; i < enemies.size(); i++)
	//	{
	//		if (enemies[i]->isCollidingWith(*this, eSide::eBullet))
	//		{
	//			enemies[i]->TakeDamage();
	//			mAlive = false;
	//		}
	//	}
	//}
}