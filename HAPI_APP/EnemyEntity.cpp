#include "EnemyEntity.h"



<<<<<<< HEAD
EnemyEntity::EnemyEntity(std::string &filename) : Entity(filename)
=======
EnemyEntity::EnemyEntity(const std::string &filename) : Entity(mSpriteName)
>>>>>>> origin/master
{
	mAlive = true;
}


EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update()
{
	HAPISPACE::VectorF position({ GetPosition() });
	SetPosition(position);
}
