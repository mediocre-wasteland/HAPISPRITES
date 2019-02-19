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
	int m_movementSpeed = 1;
	HAPISPACE::VectorF m_enemyPosition{ 500,250 };
	eDirection m_direction;
	void AIMovement();
	void ChangeDirection(eDirection newDirection);
	bool bPatrolLevel();
	bool bChasePlayer();
};

