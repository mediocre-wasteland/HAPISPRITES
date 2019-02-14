#pragma once
#include "Entity.h"
class ObstacleEntity :
	public Entity
{
public:
	ObstacleEntity();
	~ObstacleEntity();
	void Update()override final;
	eSide getSide() const override final{return mSide; }
	
};

