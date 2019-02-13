#include "PlayerEntity.h"



PlayerEntity::PlayerEntity()
{
}


PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Update()
{
	// CHECKING IF PLAYER IS ON THE GROUND
	// TEMPORARY CODE
	if (mPosition.y >= 300) // TEMPORARY code makes the "ground" where y = 300
	{
		mPosition.y = 300;
		mIsOnGround = true;
	}
	else
	{
		mIsOnGround = false;
	}

	if (mIsOnGround && CheckInput() == eDirection::eUp) // this checks if a jump is being initiated from the ground 
	{
		// JUMP START ANIMATION HERE
		mIsJumping = true;
	}
	if (CheckInput() != eDirection::eUp) // this checks if the user stops pressing the jump button and ends the jump early
	{
		// CONSIDER ADDING A FEW FRAMES OF SLOWED ASCENT FOR UPWARD MOMENTUM
		mIsJumping = false;
	}
	if (CheckInput() == eDirection::eRight && CheckInput() != eDirection::eLeft) // this checks if the user is inputing to go right but not left
	{
		// RIGHT MOVING ANIMATION HERE
		mPosition.x += mHSpeed;
	}
	if (CheckInput() == eDirection::eLeft && CheckInput() != eDirection::eRight) // this checks if the user is inputing to go left but not right
	{
		// LEFT MOVING ANIMATION HERE
		mPosition.x -= mHSpeed;
	}
	if (mIsJumping && mTimeJumped <= mMaxJumpLength) // this checks if the player is holding the jump button and the time they've been jumping is not above a certain limit (prevents infinite jumping)
	{
		// MID JUMP ANIMATION HERE
		mPosition.y -= mJumpSpeed;
		mTimeJumped++;
	}
	else
	{
		mIsJumping = false;
		mTimeJumped = 0;
	}
	if (!mIsOnGround && !mIsJumping) // if the player is not ascending and not on the ground then gravity will be applyed and send them downwards
	{
		// FALLING ANIMATION HERE
		mPosition.y += mGravity;
	}

	std::cout << "Update" << std::endl;
}

eDirection PlayerEntity::CheckInput()
{
	std::cout << "Check Input" << std::endl;
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	if (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])
	{
		return eDirection::eUp;
	}
	else if (mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT])
	{
		return eDirection::eRight;
	}
	else if (mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT])
	{
		return eDirection::eLeft;
	}
	else
	{
		return eDirection::eDown;
	}
}
