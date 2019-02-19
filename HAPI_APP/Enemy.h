#pragma once

#include "HAPISprites_Lib.h"

using namespace HAPISPACE;

enum class AIEDirection
{
	Up,
	Left,
	Down,
	Right
};

class Enemy
{
public:
	Enemy(int width, int height);
	~Enemy();
	void Update();
	void Render();
	VectorI GetPosition();
protected:

private:
	int screenWidth;
	int screenHeight;
	int m_movementSpeed = 1;
	HAPISPACE::VectorI m_enemyPosition{ 500,250 };
	AIEDirection m_direction;
	void AIMovement();
	void ChangeDirection(AIEDirection newDirection);
	bool bPatrolLevel();
	bool bChasePlayer();
};

