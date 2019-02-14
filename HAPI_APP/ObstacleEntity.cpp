#include "ObstacleEntity.h"



ObstacleEntity::ObstacleEntity()
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
