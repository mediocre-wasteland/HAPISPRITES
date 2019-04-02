#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = true;
	mSide = eSide::ePlayer;
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
	MovementCollision();
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

	SCREEN_SURFACE->DrawFilledCircle({ mLastCollidedCollisionInfo.screenPos, 4 }, ColourFill(Colour255::RED));

	SCREEN_SURFACE->DrawLine(mLastCollidedCollisionInfo.screenPos, mLastCollidedCollisionInfo.screenPos + VectorI(mLastCollidedCollisionInfo.normal * 100.0f),
		ColourFill(Colour255::WHITE), 1.0f);

	if (!mLastCollidedCollisionInfo.otherColliderName.empty())
	{
		int x{ 150 };
		int y{ 20 };
		int gap{ 15 };

		HAPI_Sprites.RenderText({ x, y }, Colour255::WHITE, "Last result: " + CollisionInfo::CollisionResultToString(mLastCollidedCollisionInfo.result) +
			" Type: " + CollisionInfo::CollisionShapeTypeToString(mLastCollidedCollisionInfo.type));
		y += gap;

		HAPI_Sprites.RenderText({ x, y }, Colour255::WHITE, "Between colliders: " + mLastCollidedCollisionInfo.thisColliderName + " and " + mLastCollidedCollisionInfo.otherColliderName);
		y += gap;

		HAPI_Sprites.RenderText({ x, y }, Colour255::WHITE, "This local pos: " + mLastCollidedCollisionInfo.thisLocalPos.ToString());
		y += gap;
	}
}

