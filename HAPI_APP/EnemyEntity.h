#pragma once
#include "Entity.h"
class EnemyEntity :
	public Entity
{
public:
	EnemyEntity(); 
	~EnemyEntity();
	void Update()override final;
	eSide getSide() const override final { return mSide; }
};

