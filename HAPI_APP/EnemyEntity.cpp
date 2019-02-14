#include "EnemyEntity.h"



EnemyEntity::EnemyEntity()
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
