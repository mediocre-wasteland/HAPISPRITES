#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(std::string &filename) : Entity(filename)
{
	mAlive = true;
	mSide = eSide::ePlayer;
	SetPosition({ 80.f, 10.f });
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

	if (isColliding == true && mLastCollidedCollisionInfo.thisLocalPos.y > sprite->FrameHeight() * 0.75) // if player is not already on ground and is colliding reacts to floor
	{
		Velocity = 0;
		mIsOnGround = true;
		mHasSecondJump = true;
		mTimeFallen = 0;
	}
	if (mIsOnGround && (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])) // this checks if a jump is being initiated from the ground 
	{
		Velocity.y = -8;
		mIsJumping = true;
	}
	if ((mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT]) && !(mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT])) // this checks if the user is inputing to go right but not left
	{
		Velocity.x = 5;
	}
	else if ((mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT]) && !(mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT])) // this checks if the user is inputing to go left but not right
	{
		Velocity.x = -5;
	}
	else if (!((mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT])) && !((mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT])))
	{
		Velocity.x = 0;

	}
	if (isColliding)
	{
		if (mLastCollidedCollisionInfo.thisLocalPos.x < sprite->FrameWidth() * 0.75 && mLastCollidedCollisionInfo.thisLocalPos.x > sprite->FrameWidth()* 0.25 &&  mLastCollidedCollisionInfo.thisLocalPos.y < sprite->FrameHeight() * 0.25) // if player is colliding and local collider position y  bounces player back down
		{//TOP COLLISION
			mIsJumping = false;
			mHasSecondJump = false;
			Velocity.y = 5;
		}
		if (mLastCollidedCollisionInfo.thisLocalPos.x < sprite->FrameWidth() * 0.45 && mLastCollidedCollisionInfo.thisLocalPos.y < sprite->FrameHeight() * 0.74 && mLastCollidedCollisionInfo.thisLocalPos.y > sprite->FrameHeight() * 0.25)// if player is on ground, colliding and local collider position x reacts to left hand obstacle and moves right
		{//LEFT COLLISION
			Velocity.x = 5;
			mIsJumping = false;
			mHasSecondJump = false;
		}
		if (mLastCollidedCollisionInfo.thisLocalPos.x > sprite->FrameWidth() *0.55 && mLastCollidedCollisionInfo.thisLocalPos.y < sprite->FrameHeight() * 0.74 && mLastCollidedCollisionInfo.thisLocalPos.y > sprite->FrameHeight() * 0.25)// if player is on ground, colliding and local collider position x reacts to right hand obstacle and moves left
		{//RIGHT COLLISION
			Velocity.x = -5;
			mIsJumping = false;
			mHasSecondJump = false;
		}
	}
	if (isColliding == false)
	{
		mIsOnGround = false;
	}
	DWORD deltaTimeMS{ HAPI_Sprites.GetTime() - timeSinceLastMove };
	if (deltaTimeMS >= MoveTime)
	{
		deltaTimeS = 0.001f * deltaTimeMS;
		timeSinceLastMove = HAPI_Sprites.GetTime();

		Velocity += (Gravity)* deltaTimeS;

		if (mIsOnGround && !(mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP]))
		{
			Velocity.y = 0;
		}
		sprite->GetTransformComp().Translate(Velocity);
		SetPosition(position + Velocity);


		timeSinceLastMove = HAPI_Sprites.GetTime();
	}
	if (Velocity.x > 0)
	{
		if (sprite->GetFrameSetName() != "RunRight")
		{
			sprite->SetAutoAnimate(10, true, "RunRight");
		}
	}
	if (Velocity.x < 0)
	{
		if (sprite->GetFrameSetName() != "RunLeft")
		{
			sprite->SetAutoAnimate(10, true, "RunLeft");
		}
	}
	if (Velocity.x == 0)
	{
		if (sprite->GetFrameSetName() != "Idle")
		{
			sprite->SetAutoAnimate(10, true, "Idle");
		}
	}
	if (Velocity.y != 0)
	{
		if (sprite->GetFrameSetName() != "Idle")
		{
			sprite->SetAutoAnimate(10, true, "Idle");
		}
	}


	isColliding = false;


	HAPI_Sprites.RenderText({50, 40}, Colour255::BLACK, "Money : " + mMoneyAmount);

	HAPI_Sprites.RenderText(0, 60, Colour255::BLACK, "Ammo : " + mLGAmmo + '/' + mLGMaxAmmo);

	HAPI_Sprites.RenderText(0, 80, Colour255::BLACK, "Key : " + mHasKey);
	
}

