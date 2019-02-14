#include "BackGroundEntity.h"



BackGroundEntity::BackGroundEntity(const std::string &filename) : Entity(mSpriteName)
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
