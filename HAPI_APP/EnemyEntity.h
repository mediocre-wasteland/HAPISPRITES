#pragma once
#include "Entity.h"
class EnemyEntity :
	public Entity
{
public:
<<<<<<< HEAD
	EnemyEntity(std::string &filename);
=======
	EnemyEntity(const std::string &filename);
>>>>>>> origin/master
	~EnemyEntity();
	void Update()override final;
	eSide GetSide() const override final { return mSide; }
};

