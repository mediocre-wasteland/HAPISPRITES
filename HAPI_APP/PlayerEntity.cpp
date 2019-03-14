#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::ePlayer;
	SetPosition({ 50.f, 0.f });
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
	std::cout << mLastCollidedCollisionInfo.thisLocalPos.ToString() << std::endl;
	HAPISPACE::VectorF position({ GetPosition() });
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();
	// CHECKING IF PLAYER IS ON THE GROUND
	// TEMPORARY CODE

	if (isColliding == true && !mIsOnGround && mLastCollidedCollisionInfo.thisLocalPos.y > sprite->FrameHeight()/1.5) // if player is not already on ground and is colliding reacts to floor
	{
		mIsOnGround = true;
		Velocity.y = 0;
		SetPosition({ GetPosition().x, GetPosition().y });
		mHasSecondJump = true;
		mTimeFallen = 0;
	}
    if  (isColliding == true && mLastCollidedCollisionInfo.thisLocalPos.y < sprite->FrameHeight() / 4) // if player is colliding and local collider position y  bounces player back down
	{
		mIsJumping = false;
		mHasSecondJump = false;
		Velocity.y = 1;
		SetPosition({ GetPosition().x , GetPosition().y + Velocity.y});
	}
	if (isColliding == true && mLastCollidedCollisionInfo.thisLocalPos.x < sprite->FrameWidth() / 4)// if player is on ground, colliding and local collider position x reacts to left hand obstacle and moves right
	{
		Velocity.x = 1;
		SetPosition({ GetPosition().x + Velocity.x, GetPosition().y });
		mIsJumping = false;
		mHasSecondJump = false;
	}
	if (isColliding == true && mLastCollidedCollisionInfo.thisLocalPos.x > sprite->FrameWidth() /1.5)// if player is on ground, colliding and local collider position x reacts to right hand obstacle and moves left
	{
		Velocity.x = -1;
		SetPosition({ GetPosition().x + Velocity.x, GetPosition().y });
		mIsJumping = false;
		mHasSecondJump = false;
	}
	if (isColliding==false)// if not colliding sets off ground
	{
		mIsOnGround = false;
	}
	if (mIsOnGround && (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])) // this checks if a jump is being initiated from the ground 
	{
		sprite->SetAutoAnimate(1, false, "Jump");
		Velocity.y = -5;
		mIsJumping = true;
	}

	if (mHasSecondJump && (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP]) && mTimeFallen > mFallingCooldown)
	{
		// SECOND JUMP START ANIMATION HERE
		mIsJumping = true;
		Velocity.y = -5;
		mHasSecondJump = false;
	}
	if ((mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT]) && !(mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT]) && !mIsDodging) // this checks if the user is inputing to go right but not left
	{
		sprite->SetAutoAnimate(1, false, "RunRight");
		if (isColliding && mLastCollidedCollisionInfo.thisLocalPos.x > sprite->FrameWidth() / 1.5)
		{
			Velocity.x = 0;
			SetPosition({ GetPosition().x, GetPosition().y });
		}
		else
		{
			Velocity.x = 5;
			SetPosition({ GetPosition().x + Velocity.x, GetPosition().y });
		}
		
	}

	if ((mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT]) && !(mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT]) && !mIsDodging) // this checks if the user is inputing to go left but not right
	{
		sprite->SetAutoAnimate(1, false, "RunLeft");
		if (isColliding && mLastCollidedCollisionInfo.thisLocalPos.x < sprite->FrameWidth() / 4)
		{
			Velocity.x = 0;
			SetPosition({ GetPosition().x + Velocity.x, GetPosition().y });
		}
		else
		{
			Velocity.x = -5;
			SetPosition({ GetPosition().x + Velocity.x, GetPosition().y });
		}
		
	}
	if (mIsJumping && mTimeJumped <= mMaxJumpLength) // this checks if the player is holding the jump button and the time they've been jumping is not above a certain limit (prevents infinite jumping)
	{
		// MID JUMP ANIMATION HERE
		//SetPosition({ GetPosition().x , GetPosition().y - ((mMaxJumpLength-mTimeJumped)/(0.5f*mMaxJumpLength))*mHSpeed });

		mTimeJumped++;

		DWORD deltaTimeMS{ HAPI_Sprites.GetTime() - timeSinceLastMove };
		if (deltaTimeMS >= MoveTime)
		{
			deltaTimeS = 0.001f * deltaTimeMS;
			timeSinceLastMove = HAPI_Sprites.GetTime();

			Acceleration += Force / Mass;
			Velocity += (Gravity + Acceleration) * deltaTimeS;

			SetPosition({ GetPosition() + Velocity });

			timeSinceLastMove = HAPI_Sprites.GetTime();
		}
	}
	else
	{
		mIsJumping = false;
		mTimeJumped = 0;
	}

	if (!mIsOnGround && !mIsJumping) // if the player is not ascending and not on the ground then gravity will be applyed and send them downwards
	{
		// FALLING ANIMATION HERE

		DWORD deltaTimeMS{ HAPI_Sprites.GetTime() - timeSinceLastMove };
		if (deltaTimeMS >= MoveTime)
		{
			deltaTimeS = 0.001f * deltaTimeMS;
			timeSinceLastMove = HAPI_Sprites.GetTime();

			Acceleration += Force / Mass;
			Velocity += (Gravity + Acceleration) * deltaTimeS;

			SetPosition({ GetPosition() + Velocity });

			timeSinceLastMove = HAPI_Sprites.GetTime();
		}

		mTimeFallen++;
	}

	

	
	isColliding = false;
	sprite->GetTransformComp().SetPosition(position);
	
	
}

