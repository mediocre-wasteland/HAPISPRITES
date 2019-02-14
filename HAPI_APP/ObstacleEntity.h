#pragma once
#include "Entity.h"
class ObstacleEntity :
	public Entity
{
public:
<<<<<<< HEAD
	ObstacleEntity(std::string &filename);
=======
	ObstacleEntity(const std::string &filename);
>>>>>>> origin/master
	~ObstacleEntity();
	void Update()override final;
	eSide GetSide() const override final{return mSide; }
	
};

