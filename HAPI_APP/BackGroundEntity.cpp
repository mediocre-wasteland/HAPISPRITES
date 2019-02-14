#include "BackGroundEntity.h"



BackGroundEntity::BackGroundEntity()
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
