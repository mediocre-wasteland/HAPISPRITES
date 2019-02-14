#include "PlayerEntity.h"



<<<<<<< HEAD
PlayerEntity::PlayerEntity(std::string &filename) : Entity(filename)
=======
PlayerEntity::PlayerEntity(const std::string &filename) : Entity(mSpriteName)
>>>>>>> origin/master
{
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Update()
{
	HAPISPACE::VectorF position({ GetPosition() });
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();
	// CHECKING IF PLAYER IS ON THE GROUND
	// TEMPORARY CODE
	if (GetPosition().y >= 300) // TEMPORARY code makes the "ground" where y = 300
	{
		SetPosition({GetPosition().x, 300});
		mIsOnGround = true;
	}
	else
	{
		mIsOnGround = false;
	}

	if (mIsOnGround && (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])) // this checks if a jump is being initiated from the ground 
	{
		// JUMP START ANIMATION HERE
		mIsJumping = true;
	}
	if (!(mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])) // this checks if the user stops pressing the jump button and ends the jump early
	{
		// CONSIDER ADDING A FEW FRAMES OF SLOWED ASCENT FOR UPWARD MOMENTUM
		mIsJumping = false;
	}
	if ((mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT]) && !(mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT])) // this checks if the user is inputing to go right but not left
	{
		// RIGHT MOVING ANIMATION HERE
		SetPosition({ GetPosition().x + mHSpeed, GetPosition().y });
	}
	if ((mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT]) && !(mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT])) // this checks if the user is inputing to go left but not right
	{
		// LEFT MOVING ANIMATION HERE
		SetPosition({ GetPosition().x - mHSpeed, GetPosition().y });
	}
	if (mIsJumping && mTimeJumped <= mMaxJumpLength) // this checks if the player is holding the jump button and the time they've been jumping is not above a certain limit (prevents infinite jumping)
	{
		// MID JUMP ANIMATION HERE
		SetPosition({ GetPosition().x , GetPosition().y - mHSpeed });
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
		SetPosition({ GetPosition().x , GetPosition().y + mHSpeed });
	}
	sprite->GetTransformComp().SetPosition(position);
	std::cout << "Update" << std::endl;
}

