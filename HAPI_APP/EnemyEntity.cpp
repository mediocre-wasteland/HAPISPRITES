#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mHasSecondJump = true;
	mSide = eSide::eEnemy;
	mEnemyPosition = { 300.0f, 550.0f };
}

EnemyEntity::~EnemyEntity()
{

}

void EnemyEntity::Update()
{
	// Movement Checks
	AIMovement();
	// Setting Position At The End Of Each Update
	sprite->GetTransformComp().SetPosition(mEnemyPosition);
}

void EnemyEntity::AIMovement()
{
	// Instructions For AI To Follow If It's Just Patrolling And On The Screen
	if (!bChasePlayer() && !bEnemyOffScreen)
	{
		//std::cout << "In AIMovement() - bPatrolLevel() - Patrolling Level" << std::endl;

		// Randomly Generates A Direction For The AI To Go In
		if (std::rand() % 100 == 0)
		{
			ChangeDirection((eDirection)(rand() % 2));
			// Including Jumping
			//ChangeDirection((eDirection)(rand() % 3));
		}

		// Checks Which Direction Is Chosen
		switch (mDirection)
		{
			// Case For Jumping
			/*case eDirection::eUp:
			{
				std::cout << "In AIMovement() - bPatrolLevel() - Jumping" << std::endl;

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
			break;*/
		case eDirection::eRight:
		{
			//std::cout << "In AIMovement() - bPatrolLevel() - Going Right" << std::endl;

			mEnemyPosition.x += mHSpeed;
			mIsJumping = false;
			sprite->GetTransformComp().SetPosition({ mEnemyPosition.x, mEnemyPosition.y });
		}
		break;
		case eDirection::eLeft:
		{
			//std::cout << "In AIMovement() - bPatrolLevel() - Going Left" << std::endl;

			mEnemyPosition.x -= mHSpeed;
			mIsJumping = false;
			sprite->GetTransformComp().SetPosition({ mEnemyPosition.x, mEnemyPosition.y });
		}
		break;
		default:
			break;
		}
	}

	/// Checking Which Side Player Is On And Moving Towards Him
	// Going To The Left
	if (bChasePlayer() && bPlayerOnLeft && !bEnemyOffScreen)
	{
		mEnemyPosition.x -= mHSpeed;
		sprite->GetTransformComp().SetPosition({ mEnemyPosition.x, mEnemyPosition.y });
	}
	// Going To The Right
	if (bChasePlayer() && bPlayerOnRight && !bEnemyOffScreen)
	{
		mEnemyPosition.x += mHSpeed;
		sprite->GetTransformComp().SetPosition({ mEnemyPosition.x, mEnemyPosition.y });
	}

	/// Checking For Going Off Screen
	// Checks To Make Sure It Doesnt Go Off The Sides Of The Screen
	if (mEnemyPosition.x < 0)
	{
		bEnemyOffScreen = true;
	}
	else if (mEnemyPosition.x > screenWidth)
	{
		bEnemyOffScreen = true;
	}
	else
	{
		bEnemyOffScreen = false;
	}

	if (mEnemyPosition.x == 0)
	{
		ChangeDirection(eDirection::eRight);
	}
	if (mEnemyPosition.x == screenWidth)
	{
		ChangeDirection(eDirection::eLeft);
	}

	/// Checking For Floor
	if (mEnemyPosition.y >= 550.0f)
	{
		mIsOnGround = true;
	}

	/// Jumping
	// Causes Initial Jump And Makes Sure It Doesnt Go Above The Specified Limit To Prevent Infinite Jumping
	if (mIsJumping && mTimeJumped <= mMaxJumpLength)
	{
		// TODO: Get The Enemy To Jump In An Arc Motion Rather Than Just Straight Up
		mIsOnGround = false;
		// Applies Jump Force To The Enemy
		sprite->GetTransformComp().SetPosition({ mEnemyPosition.x, mEnemyPosition.y - ((mMaxJumpLength - mTimeJumped) / (0.5f*mMaxJumpLength)) * mHSpeed });
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
		sprite->GetTransformComp().SetPosition({ mEnemyPosition.x, mEnemyPosition.y + mGravity });
		mTimeFallen++;
	}
}

// Function Controlling The Change In AI's Direction
void EnemyEntity::ChangeDirection(eDirection newDirection)
{
	mDirection = newDirection;
}

bool EnemyEntity::bChasePlayer()
{
	// If Player Is Within The Enemies Scan Range, Begin To Chase Player

	//	NOTE: I've Had To Add 125 To The Equation Because The Enemy Was Spotting The Player When Inside Of Him And Was Saying That He Was To The Right Of Him And Then Once The Player Was
	//	Actually To The Right Of The Enemy, It Would Say That It Couldnt Find The Player So Adding In The Extra 125 Means That When The Player Is Inside The Enemy, He HASN'T Been Spotted
	//	But When He's Within The Range, Either To The Left Or The Right, He IS Spotted By The Enemy As Originally Planned
	if (playerPosition.x > mEnemyPosition.x + 125 && playerPosition.x < mEnemyPosition.x + 125 + mScanRange)
	{
		bPlayerOnLeft = false;
		bPlayerOnRight = true;
		//std::cout << "In bChasePlayer() - Spotted Player To The Right Of Me" << std::endl;
		return true;
	}
	if (playerPosition.x < mEnemyPosition.x && playerPosition.x > mEnemyPosition.x - mScanRange)
	{
		bPlayerOnRight = false;
		bPlayerOnLeft = true;
		//std::cout << "In bChasePlayer() - Spotted Player To The Left Of Me" << std::endl;
		return true;
	}
	else
	{
		//std::cout << "In bChasePlayer() - No Sign Of Player - Will Patrol" << std::endl;
		return false;
	}
}

void EnemyEntity::TakeDamage()
{
	mIsHit = true;
}