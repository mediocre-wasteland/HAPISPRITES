#pragma once
#include "Entity.h"
class PlayerEntity :
	public Entity
{
public:
	PlayerEntity(std::string &filename);
	~PlayerEntity();

	virtual void Update() override;

	virtual eSide GetSide() const override { return mSide; } 
	virtual eDirection GetDirection() const override { return  mDirection; }

private:
	int mMaxJumpLength{ 100 }; // the max amount of updates the player can move vertically from a jump
	bool mIsJumping{ false }; // whether or not the space bar is held and player has not reached max jump height
	bool mIsOnGround{ false }; // whether or not the player has terrain directly below them
	float mHSpeed{ 3 }; // the horizontal speed, how fast the player will move along the x axis
	float mJumpSpeed{ 3 }; // the upwards speed, how fast the player will move positively along the y axis
	float mGravity{ 1 }; // how many pixels the player will fall per update
	int mTimeJumped{ 0 }; // how many updates the player has moved vertically since start of jump
};

