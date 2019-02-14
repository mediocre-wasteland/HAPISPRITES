#pragma once
#include "Entity.h"
class EnemyEntity :
	public Entity
{
public:
	EnemyEntity(std::string &filename);

	~EnemyEntity();
	void Update()override final;
	eSide GetSide() const override final { return mSide; }
};

