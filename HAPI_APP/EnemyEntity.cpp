#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = true;
	mHasSecondJump = true;
	mSide = eSide::eEnemy;
	// Position For Enemy To Be On Creation (550 = Floor)
	SetPosition({ 500.0f, 550.0f });
}

EnemyEntity::~EnemyEntity()
{

}

void EnemyEntity::Update()
{
	HAPISPACE::VectorF mEnemyPosition{ GetPosition() };
	// Movement Checks
	AIMovement(mEnemyPosition);
	// Setting Position At The End Of Each Update
	sprite->GetTransformComp().SetPosition(GetPosition());
}

void EnemyEntity::AIMovement(HAPISPACE::VectorF mEnemyPosition)
{
	// Randomly Generates A Direction For The AI To Go In
	if (std::rand() % 100 == 0)
	{
		ChangeDirection((eDirection)(rand() % 3));
	}

	// Instructions For AI To Follow If It's Just Patrolling
	if (bPatrolLevel())
	{
		switch (mDirection)
		{
		case eDirection::eUp:
		{
			if (mIsOnGround)
			{
				mTimeFallen = 0;
				mIsJumping = true;
				mHasSecondJump = true;
			}
			if (mHasSecondJump && mTimeFallen > mFallingCooldown)
			{
				mIsJumping = true;
				mHasSecondJump = false;
			}
		}
		break;
		case eDirection::eRight:
		{
			mEnemyPosition.x += mHSpeed;
			mIsJumping = false;
			SetPosition({ mEnemyPosition.x, mEnemyPosition.y });
		}
		break;
		case eDirection::eLeft:
		{
			mEnemyPosition.x -= mHSpeed;
			mIsJumping = false;
			SetPosition({ mEnemyPosition.x, mEnemyPosition.y });
		}
		break;
		default:
			break;
		}
	}

	// TODO: Functions If Chasing Player
	if (bChasePlayer())
	{

	}

	// Checks To Make Sure It Doesnt Go Off The Sides Of The Screen
	/*if (mEnemyPosition.x <= 0)
	{
		ChangeDirection(eDirection::eRight);
	}
	if (mEnemyPosition.x >= 1025)
	{
		ChangeDirection(eDirection::eLeft);
	}*/


	// Prevents Going Off The Top Of The Screen
	if (mEnemyPosition.y <= 0)
	{
		mIsJumping = false;
		mTimeFallen++;
	}

	/// Checking For Floor
	if (mEnemyPosition.y >= 550.0f)
	{
		mIsOnGround = true;
	}

	/// Jumping
	// Causes Initial Jump And Makes Sure It Doesnt Go Above The Specified Limit To Prevent Infinite Jumping
	// TODO: Get The AI To Jump In The Direction It's Going Rather Than Just Straight Up
	if (mIsJumping && mTimeJumped <= mMaxJumpLength)
	{
		mIsOnGround = false;
		// Applies Jump Force To The AI
		SetPosition({ GetPosition().x , GetPosition().y - ((mMaxJumpLength - mTimeJumped) / (0.5f*mMaxJumpLength))*mHSpeed });
		mTimeJumped++;
	}
	else
	{
		// If Jump Limit Has Been Reached
		mIsJumping = false;
		mTimeJumped = 0;
	}
	
	/// Gravity
	// Checks To See If AI Is Both Off The Ground And Not Jumping/In The Air
	if (!mIsOnGround && !mIsJumping)
	{
		// Applies Gravity
		SetPosition({ GetPosition().x , GetPosition().y + mGravity });
		mTimeFallen++;
	}
}

// Function Controlling The Change In AI's Direction
void EnemyEntity::ChangeDirection(eDirection newDirection)
{
	mDirection = newDirection;
}

bool EnemyEntity::bPatrolLevel()
{
	if(!bChasePlayer())
	{
		return true;
	}
	
	return false;
}

// TODO: Need A Way Of Getting Player Position
bool EnemyEntity::bChasePlayer()
{
	//if(/*SpotsPlayer*/)
	/*{
		return true;
	}*/

	return false;
}

void EnemyEntity::TakeDamage()
{
	mIsHit = true;
	std::cout << "Enemy Hit" << std::endl;
}