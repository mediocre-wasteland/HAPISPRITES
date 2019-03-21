#pragma once
#include "Entity.h"
class ObstacleEntity :
	public Entity
{
public:

	ObstacleEntity(std::string &fileName);
	~ObstacleEntity();
	void Update()override final;
	eSide GetSide() const override final{return mSide; }
	eDirection GetDirection() const override final { return mDirection; }
	
};

