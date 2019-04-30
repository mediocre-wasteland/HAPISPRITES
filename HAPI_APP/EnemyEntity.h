#pragma once
#include "Entity.h"

class EnemyEntity :
	public Entity
{
public:
	EnemyEntity(std::string &filename);
	~EnemyEntity();
	void Update()override final;
	eSide GetSide() const override final { return mSide; }
	eDirection GetDirection() const override final { return mDirection; }
	void TakeDamage();

protected:

private:
	int mTimeJumped{ 0 };
	int mTimeFallen{ 0 };
	int mScanRange{ 125 };
	int screenWidth = 1280;
	int screenHeight = 832;
	int mMaxJumpLength{ 80 };
	int mFallingCooldown{ 25 };
	bool bChasePlayer();
	bool mIsJumping{ false };
	bool mIsOnGround{ false };
	bool bPlayerOnLeft{ false };
	bool bPlayerOnRight{ false };
	bool mHasSecondJump{ false };
	bool bEnemyOffScreen{ false };
	float mHSpeed{ 2 };
	float mGravity{ 1.5f };
	float mJumpSpeed{ 1.5f };
	void ChangeDirection(eDirection newDirection);
	void AIMovement();
	bool mIsHit{ false };
	HAPISPACE::VectorF mEnemyPosition;
};

