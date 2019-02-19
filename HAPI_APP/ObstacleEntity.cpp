#include "ObstacleEntity.h"
ObstacleEntity::ObstacleEntity(std::string &filename) : Entity(filename)

{
	mAlive = true;
}


ObstacleEntity::~ObstacleEntity()
{
}

void ObstacleEntity::Update()
{
	sprite->GetTransformComp().SetPosition(GetPosition());
}
