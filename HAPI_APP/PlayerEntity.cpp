#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::ePlayer;
	SetPosition({ 0.f, 560.f });
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::AddMoney(int amount) 
{ 
	mMoneyAmount += amount; 
	if (mMoneyAmount < 0) // checks if the player has lost more money than they have left and if so marks them as bankrupt
	{
		mBankrupt = true;
	}
}

void PlayerEntity::AddLGAmmo(int amount)
{
	mLGAmmo += amount;
	if (mLGAmmo > mLGMaxAmmo) // if the ammo total reaches a number above capacity it is set back to capacity
	{
		mLGAmmo = mLGMaxAmmo;
	}
	if (mLGAmmo < 0) // makes sure the player cannot have negative ammo
	{
		mLGAmmo = 0;
	}
}

void PlayerEntity::ShootLG()
{
	// SHOOTING ANIMATION HERE
	// PROJECTILE SHOOTING HERE
	AddLGAmmo(-1);
}

void PlayerEntity::Update()
{
	//sprite->SetAutoAnimate(5, true, "Player");

	HAPISPACE::VectorF position({ GetPosition() });
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();
	// CHECKING IF PLAYER IS ON THE GROUND
	// TEMPORARY CODE
	if (isColliding == true) // TEMPORARY code makes the "ground" where y = 300
	{
		mIsOnGround = true;
		mHasSecondJump = true;
		mTimeFallen = 0;
	}

	if (isColliding==false)
	{
		mIsOnGround = false;
	}

	if (mIsOnGround && (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])) // this checks if a jump is being initiated from the ground 
	{
		// JUMP START ANIMATION HERE
		mIsJumping = true;
	}
	if (mHasSecondJump && (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP]) && mTimeFallen > mFallingCooldown)
	{
		// SECOND JUMP START ANIMATION HERE
		mIsJumping = true;
		mHasSecondJump = false;
	}
	if ((mKeyboardInput.scanCode[HK_CONTROL] || mKeyboardInput.scanCode[HK_LSHIFT]) && mIsOnGround) // checks if either of the dodge keys are pressed and if the player is on the ground and if so they can sneak
	{
		mSneaking = true;
	}
	else
	{
		mSneaking = false;
	}
	if ((mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT]) && !(mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT]) && !mIsDodging) // this checks if the user is inputing to go right but not left
	{
		if (!mSneaking)
		{
			// RIGHT MOVING ANIMATION HERE
			SetPosition({ GetPosition().x + mHSpeed, GetPosition().y });
		}
		else
		{
			// SNEAK RIGHT ANIMATION HERE
			SetPosition({ GetPosition().x + mHSpeed/3, GetPosition().y });
		}
	}
	if ((mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT]) && !(mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT]) && !mIsDodging) // this checks if the user is inputing to go left but not right
	{
		if (!mSneaking)
		{
			// LEFT MOVING ANIMATION HERE
			SetPosition({ GetPosition().x - mHSpeed, GetPosition().y });
		}
		else
		{
			// SNEAK LEFT ANIMATION HERE
			SetPosition({ GetPosition().x - mHSpeed/3, GetPosition().y });
		}
		
	}

	// Dodging code
	if (mKeyboardInput.scanCode['Q'] && mTimeSinceDodge >= mDodgecooldown) // These two if statements check if the dodge left or dodge right buttons are pressed and if so starts a dodge accordingly
	{
		mIsDodging = true;
		mDodgeLastFacingLeft = true;
		mVunerable = false;
		mTimeDodged = 0;
		mTimeSinceDodge = 0;
	}
	if (mKeyboardInput.scanCode['E'] && mTimeSinceDodge >= mDodgecooldown)
	{
		mIsDodging = true;
		mDodgeLastFacingLeft = false;
		mVunerable = false;
		mTimeDodged = 0;
		mTimeSinceDodge = 0;
	}
	if (mIsDodging && mTimeDodged < mMaxDodgeLength) // this checks if the player is dodging and if the amount of updates they can dodge for has passed
	{
		if (mDodgeLastFacingLeft)
		{
			// DODGE LEFT ANIMATION HERE
			SetPosition({ GetPosition().x - 1.5f * mHSpeed, GetPosition().y }); // they move at 1.5 time speed while dodging
		}
		else
		{
			// DODGE LEFT ANIMATION HERE
			SetPosition({ GetPosition().x + 1.5f * mHSpeed, GetPosition().y });
		}
		mTimeDodged++;
	}
	else // when they aren't dodging the isDodging bool is updated and they are no longer invunerable
	{
		mIsDodging = false;
		mVunerable = true;
	}
	if (mTimeSinceDodge < mDodgecooldown) // this ticks up until the player can dodge again
	{
		mTimeSinceDodge++;
	}
	// Dodging code

	if (mIsJumping && mTimeJumped <= mMaxJumpLength) // this checks if the player is holding the jump button and the time they've been jumping is not above a certain limit (prevents infinite jumping)
	{
		// MID JUMP ANIMATION HERE
		SetPosition({ GetPosition().x , GetPosition().y - ((mMaxJumpLength-mTimeJumped)/(0.5f*mMaxJumpLength))*mHSpeed });
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
		SetPosition({ GetPosition().x , GetPosition().y + mGravity });
		mTimeFallen++;
	}
	isColliding = false;
	sprite->GetTransformComp().SetPosition(position);
}

