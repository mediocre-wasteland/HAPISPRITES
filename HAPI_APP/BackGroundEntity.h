#pragma once
#include "Entity.h"
class BackGroundEntity :
	public Entity
{
public:
<<<<<<< HEAD
	BackGroundEntity(std::string &filename);
=======
	BackGroundEntity(const std::string &filename);
>>>>>>> origin/master
	~BackGroundEntity();
	void Update()override final;
	eSide GetSide() const override final { return mSide; }
};

