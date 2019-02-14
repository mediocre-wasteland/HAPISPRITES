#include "BackGroundEntity.h"

BackGroundEntity::BackGroundEntity(std::string &filename) : Entity(filename)


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
