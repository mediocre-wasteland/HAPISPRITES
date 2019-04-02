#include "ObstacleEntity.h"
ObstacleEntity::ObstacleEntity(std::string &fileName) : Entity(fileName)

{
	mAlive = true;
	mSide = eSide::eObstacle;
}


ObstacleEntity::~ObstacleEntity()
{
}

void ObstacleEntity::Update()
{
	//sprite->GetTransformComp().SetPosition(GetPosition());
	
}
