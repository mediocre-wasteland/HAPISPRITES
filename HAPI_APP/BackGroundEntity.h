#pragma once
#include "Entity.h"
class BackGroundEntity :
	public Entity
{
public:
	BackGroundEntity(std::string &filename);
	~BackGroundEntity();
	void Update()override final;
	eSide GetSide() const override final { return mSide; }
	eDirection GetDirection() const override final { return mDirection; }
};

