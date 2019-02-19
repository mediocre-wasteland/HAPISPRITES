#include "EnemyEntity.h"
EnemyEntity::EnemyEntity(std::string &filename) : Entity(filename)
{
	mAlive = true;
}


EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update()
{
	sprite->GetTransformComp().SetPosition(GetPosition());
}

void EnemyEntity::Update()
{
	AIMovement();
	std::cout << "Px: " << m_enemyPosition.x << std::endl;
	std::cout << "Py: " << m_enemyPosition.y << std::endl;
}


void EnemyEntity::AIMovement()
{
	if (bPatrolLevel())
	{
		switch (m_direction)
		{
		case eDirection::eUp:
		{
			m_enemyPosition.y -= m_movementSpeed;
		}
		break;
		case eDirection::eLeft:
		{
			m_enemyPosition.x -= m_movementSpeed;
		}
		break;
		case eDirection::eDown:
		{
			m_enemyPosition.y += m_movementSpeed;
		}
		break;
		case eDirection::eRight:
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
		ChangeDirection((eDirection)(rand() % 4));
	}

	if (m_enemyPosition.x <= 0)
	{
		ChangeDirection(eDirection::eRight);
	}
	if (m_enemyPosition.x >= screenWidth)
	{
		ChangeDirection(eDirection::eLeft);
	}
	if (m_enemyPosition.y <= 0)
	{
		ChangeDirection(eDirection::eDown);
		std::cout << "Ive Gone Off The Top Of The Screen" << std::endl;
	}
	if (m_enemyPosition.y >= screenHeight)
	{
		ChangeDirection(eDirection::eUp);
	}


	// TODO: Add Conditions For Enemy e.g. If They Gain/Lose Sight Of The Player Or Come Close To A Wall etc. Go In The Opposite Direction
}

void EnemyEntity::ChangeDirection(eDirection newDirection)
{
	m_direction = newDirection;
}

bool EnemyEntity::bPatrolLevel()
{
	if (!bChasePlayer())
	{
		return true;
	}

	return false;
}

bool EnemyEntity::bChasePlayer()
{
	/*if(EnemySeesPlayer)
	{
		return true;
	}*/

	return false;
}
