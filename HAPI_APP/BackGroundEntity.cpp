#include "BackGroundEntity.h"



<<<<<<< HEAD
BackGroundEntity::BackGroundEntity(std::string &filename) : Entity(filename)
=======
BackGroundEntity::BackGroundEntity(const std::string &filename) : Entity(mSpriteName)
>>>>>>> origin/master
{
	mAlive = true;
}


BackGroundEntity::~BackGroundEntity()
{
}

void BackGroundEntity::Update()
{
	HAPISPACE::VectorF position({ GetPosition() });
	SetPosition(position);
}
