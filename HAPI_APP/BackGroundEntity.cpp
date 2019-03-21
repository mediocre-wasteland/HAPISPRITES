#include "BackGroundEntity.h"

BackGroundEntity::BackGroundEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = true;
	mSide = eSide::eNeutral;
}


BackGroundEntity::~BackGroundEntity()
{
}

void BackGroundEntity::Update()
{
	sprite->GetTransformComp().SetPosition(GetPosition());
}
