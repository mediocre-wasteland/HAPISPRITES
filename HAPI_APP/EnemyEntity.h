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
protected:

private:
	int screenWidth;
	int screenHeight;
	int m_movementSpeed = 1;
	HAPISPACE::VectorI m_enemyPosition{ 500,250 };
	eDirection m_direction;
	void AIMovement();
	void ChangeDirection(eDirection newDirection);
	bool bPatrolLevel();
	bool bChasePlayer();
};

