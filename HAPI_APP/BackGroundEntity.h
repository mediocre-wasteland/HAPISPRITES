#pragma once
#include "Entity.h"
class BackGroundEntity :
	public Entity
{
public:
	BackGroundEntity();
	~BackGroundEntity();
	void Update()override final;
	eSide getSide() const override final { return mSide; }
};

