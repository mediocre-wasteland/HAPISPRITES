#pragma once
#include "Entity.h"


class EnemyEntity :
	public Entity
{
public:
	EnemyEntity(std::string &fileName);
	~EnemyEntity();
	void Update()override final;
	eSide GetSide() const override final { return mSide; }
	eDirection GetDirection() const override final { return mDirection; }

protected:

private:
	int mTimeJumped{ 0 };
	int mTimeFallen{ 0 };
	int screenWidth = 1280;
	int screenHeight = 832;
	int mMaxJumpLength{ 80 };
	int mFallingCooldown{ 25 };
	bool bPatrolLevel();
	bool bChasePlayer();
	bool mIsJumping{ false };
	bool mIsOnGround{ false };
	bool mHasSecondJump{ false };
	float mHSpeed{ 2 };
	float mGravity{ 1.5f };
	float mJumpSpeed{ 1.5f };
	void ChangeDirection(eDirection newDirection);
	void AIMovement(HAPISPACE::VectorF mEnemyPosition);
};

