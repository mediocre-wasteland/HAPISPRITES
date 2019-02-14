#include "ObstacleEntity.h"



<<<<<<< HEAD
ObstacleEntity::ObstacleEntity(std::string &filename) : Entity(filename)
=======
ObstacleEntity::ObstacleEntity(const std::string &filename) : Entity(mSpriteName)
>>>>>>> origin/master
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
