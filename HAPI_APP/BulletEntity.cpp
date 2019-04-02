#include "BulletEntity.h"



BulletEntity::BulletEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = true;
	//SetPosition(VectorF(-10.f, -10.f));
}


BulletEntity::~BulletEntity()
{
}

void BulletEntity::Update(std::vector<EnemyEntity> enemies)
{
	//switch (mDirection) // this switch statement checks whether the bullet should go left or right and makes continually go that way
	//{
	//case(eDirection::eRight):
	//	SetPosition(VectorF(GetPosition().x + mSpeed, GetPosition().y));
	//	break;
	//case(eDirection::eLeft):
	//	SetPosition(VectorF(GetPosition().x - mSpeed, GetPosition().y));
	//	break;
	//default:
	//	std::cerr << "Bullet direction not left or right" << std::endl;
	//	break;
	//}
	//if (GetPosition().x < 0 || GetPosition().x > mScreenSize.x || GetPosition().y < 0 || GetPosition().y > mScreenSize.y) // this deletes the bullet if it goes offscreen TODO CONSIDER HAVING THE BULLET RELEASED FROM MEMORY RATHER THAN NOT ALIVE
	//{
	//	mAlive = false;
	//	return;
	//}
	//if (isColliding)
	//{
	//	for (int i = 0; i < enemies.size(); i++)
	//	{
	//		if (enemies[i].isCollidingWith(*this, eSide::eBullet))
	//		{
	//			enemies[i].TakeDamage();
	//			mAlive = false;
	//		}
	//	}
	//}
}