#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = true;
	mSide = eSide::ePlayer;
	SetPosition({ 80.f, 576.f });
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
	HAPISPACE::VectorF position({ GetPosition() });
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	//JUMP
	if (mIsOnGround && (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP]))
	{
		Velocity.y = -10;
		mIsJumping = true;
	}

	//MOVE LEFT / RIGHT
	if (mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT])
	{
		Velocity.x = 4;
	}
	else if (mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT])
	{
		Velocity.x = -4;
	}
	else
	{
		Velocity.x = 0;
	}

	//COLLISION CHECKS
	if (isColliding)
	{
		//BOT COLLISION
		if (mLastCollidedCollisionInfo.thisLocalPos.y > mLastCollidedCollisionInfo.otherLocalPos.y)
		{
			mIsOnGround = true;
		}

		//TOP COLLISION
		if (mLastCollidedCollisionInfo.thisLocalPos.y < mLastCollidedCollisionInfo.otherLocalPos.y)
		{
			Velocity.y = 5;
			mIsJumping = false;
		}

		//LEFT COLLISION 
		if (mLastCollidedCollisionInfo.thisLocalPos.x < mLastCollidedCollisionInfo.otherLocalPos.x && mLastCollidedCollisionInfo.thisLocalPos.y < sprite->FrameHeight() - 8)
		{
			Velocity.x = 8;
			mIsJumping = false;
		}

		//RIGHT COLLISION
		if (mLastCollidedCollisionInfo.thisLocalPos.x > mLastCollidedCollisionInfo.otherLocalPos.x && mLastCollidedCollisionInfo.thisLocalPos.y < sprite->FrameHeight() - 8)
		{
			Velocity.x = -8;
			mIsJumping = false;
		}
	}
	else
	{
		mIsOnGround = false;
	}

	//PHYSICS LOOP
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

	//ANIMATION
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
	
}

void PlayerEntity::Render()
{
	if (mAlive)
	{
		sprite->Render(SCREEN_SURFACE);
	}
	HAPI_Sprites.RenderText({ 10, 40 }, Colour255::BLACK, "Money : " + std::to_string(mMoneyAmount));

	HAPI_Sprites.RenderText(10, 60, Colour255::BLACK, "Ammo : " + std::to_string(mLGAmmo));

	HAPI_Sprites.RenderText(10, 80, Colour255::BLACK, "Key : " + std::to_string(mHasKey));
}

