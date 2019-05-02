#include "BackGroundEntity.h"

BackGroundEntity::BackGroundEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = true;
	mSide = eSide::eNeutral;
	mPosition = { 0,0 };
}


BackGroundEntity::~BackGroundEntity()
{
}

void BackGroundEntity::Update()
{
}
