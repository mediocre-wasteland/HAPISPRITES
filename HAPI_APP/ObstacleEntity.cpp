#include "ObstacleEntity.h"



ObstacleEntity::ObstacleEntity(const std::string &filename) : Entity(mSpriteName)
{
	mAlive = true;
}


ObstacleEntity::~ObstacleEntity()
{
}

void ObstacleEntity::Update()
{
	HAPISPACE::VectorF position({ GetPosition() });
	SetPosition(position);
}
