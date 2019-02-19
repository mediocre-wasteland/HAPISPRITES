#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	AIMovement();
	std::cout << "Px: " << m_enemyPosition.x << std::endl;
	std::cout << "Py: " << m_enemyPosition.y << std::endl;
}

void Enemy::Render()
{

}

VectorI Enemy::GetPosition()
{
	return m_enemyPosition;
}

void Enemy::AIMovement()
{
	if (bPatrolLevel())
	{
		switch (m_direction)
		{
		case AIEDirection::Up:
		{
			m_enemyPosition.y -= m_movementSpeed;
		}
		break;
		case AIEDirection::Left:
		{
			m_enemyPosition.x -= m_movementSpeed;
		}
		break;
		case AIEDirection::Down:
		{
			m_enemyPosition.y += m_movementSpeed;
		}
		break;
		case AIEDirection::Right:
		{
			m_enemyPosition.x += m_movementSpeed;
		}
		break;
		default:
			break;
		}
	}

	if (bChasePlayer())
	{
		// TODO: Go In The Direction The Player Is Going
		// TODO: Make A Map And Check Tiles Function
	}

	if (std::rand() % 100 == 0)
	{
		ChangeDirection((AIEDirection)(rand() % 4));
	}
		
	if (m_enemyPosition.x <= 0)
	{
		ChangeDirection(AIEDirection::Right);
	}
	if (m_enemyPosition.x >= screenWidth)
	{
		ChangeDirection(AIEDirection::Left);
	}
	if (m_enemyPosition.y <= 0)
	{
		ChangeDirection(AIEDirection::Down);
		std::cout << "Ive Gone Off The Top Of The Screen" << std::endl;
	}
	if (m_enemyPosition.y >= screenHeight)
	{
		ChangeDirection(AIEDirection::Up);
	}
		

	// TODO: Add Conditions For Enemy e.g. If They Gain/Lose Sight Of The Player Or Come Close To A Wall etc. Go In The Opposite Direction
}

void Enemy::ChangeDirection(AIEDirection newDirection)
{
	m_direction = newDirection;
}

bool Enemy::bPatrolLevel()
{
	if (!bChasePlayer())
	{
		return true;
	}

	return false;
}

bool Enemy::bChasePlayer()
{
	/*if(EnemySeesPlayer)
	{
		return true;
	}*/

	return false;
}
