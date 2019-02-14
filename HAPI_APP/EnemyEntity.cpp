#include "EnemyEntity.h"



EnemyEntity::EnemyEntity(const std::string &filename) : Entity(mSpriteName)
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
