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
	eDirection GetDirection() const override final { return mDirection; }
protected:

private:
	int screenWidth = 1280;
	int screenHeight= 832;
	int mMovementSpeed = 1;
	HAPISPACE::VectorF mEnemyPosition{ 500,550 };

	void AIMovement();
	void ChangeDirection(eDirection newDirection);
	bool bPatrolLevel();
	bool bChasePlayer();
};

