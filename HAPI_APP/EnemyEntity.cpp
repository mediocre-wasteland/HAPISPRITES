#include "EnemyEntity.h"
EnemyEntity::EnemyEntity(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::eEnemy;
	SetPosition(mEnemyPosition);
}


EnemyEntity::~EnemyEntity()
{

}


void EnemyEntity::Update()
{
	AIMovement();
	SetPosition(mEnemyPosition);
	sprite->GetTransformComp().SetPosition(GetPosition());
}


void EnemyEntity::AIMovement()
{
	mEnemyPosition = GetPosition();

	if (bPatrolLevel())
	{
		switch (mDirection)
		{
		case eDirection::eUp:
		{
			//mEnemyPosition.y -= mMovementSpeed;
		}
		break;
		case eDirection::eLeft:
		{
			mEnemyPosition.x -= mMovementSpeed;
		}
		break;
		case eDirection::eDown:
		{
			//mEnemyPosition.y += mMovementSpeed;
		}
		break;
		case eDirection::eRight:
		{
			mEnemyPosition.x += mMovementSpeed;
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

	if (mEnemyPosition.x <= 0)
	{
		ChangeDirection(eDirection::eRight);
	}
	if (mEnemyPosition.x >= screenWidth)
	{
		ChangeDirection(eDirection::eLeft);
	}
	if (mEnemyPosition.y <= 0)
	{
		ChangeDirection(eDirection::eDown);
		// TODO DEBUG std::cout << "Ive Gone Off The Top Of The Screen" << std::endl;
	}
	if (mEnemyPosition.y >= screenHeight)
	{
		ChangeDirection(eDirection::eUp);
	}


	// TODO: Add Conditions For Enemy e.g. If They Gain/Lose Sight Of The Player Or Come Close To A Wall etc. Go In The Opposite Direction
}

void EnemyEntity::ChangeDirection(eDirection newDirection)
{
	mDirection = newDirection;
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
