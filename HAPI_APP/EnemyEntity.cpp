#include "EnemyEntity.h"
EnemyEntity::EnemyEntity(std::string &filename) : Entity(filename)
{
	mAlive = true;
}


EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update()
{
	sprite->GetTransformComp().SetPosition(GetPosition());
}
