#pragma once
#include "Entity.h"
class ObstacleEntity :
	public Entity
{
public:
	ObstacleEntity(const std::string &filename);
	~ObstacleEntity();
	void Update()override final;
	eSide GetSide() const override final{return mSide; }
	
};

