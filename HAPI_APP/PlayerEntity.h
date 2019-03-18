#pragma once
#include "Entity.h"
class PlayerEntity :
	public Entity
{
public:
	PlayerEntity(std::string &filename);
	~PlayerEntity();

	virtual void Update() override;
	void AddMoney(int amount); // Increases or decreases money amount
	void AddLGAmmo(int amount); // Increases Love Gun(tm) ammo but not beyond the maximum amount
	void ShootLG(); // UNFINISHED code to shoot the Love Gun 

	virtual eSide GetSide() const override final{ return mSide; } 
	virtual eDirection GetDirection() const override final{ return  mDirection; }

private:

	///Physics
	VectorF Gravity{ 0, 9.81f};
	VectorF Velocity{ 0, 0 };
	float deltaTimeS;

	const DWORD MoveTime{ 20 };
	DWORD timeSinceLastMove{ HAPI_Sprites.GetTime() - 16};


	///Movement
	int mMaxJumpLength{ 80 }; // the max amount of updates the player can move vertically from a jump
	bool mIsJumping{ false }; // whether or not the space bar is held and player has not reached max jump height
	bool mIsOnGround{ false }; // whether or not the player has terrain directly below them
	int mTimeJumped{ 0 }; // how many updates the player has moved vertically since start of jump
	bool mHasSecondJump{ false }; // whether or not the player has a second jump they can deploy mid air
	int mTimeFallen{ 0 }; // how many updates have passed since the player has started falling
	int mFallingCooldown{ 25 }; // how many updates must pass before the second jump may be initiated


	///Collectables
	int mMoneyAmount; // the amount of money the player has. a sort of "health system" as a player loses some as they get "hit"
	bool mBankrupt{ false }; // whether or not the player has lost all money and thus the game
	int mLGAmmo; // the amount of love gun ammo the player currently has
	int mLGMaxAmmo; // the maximum ammount of love gun ammo the player can hold
	bool mHasKey{ false }; // Check if the player has a key
};

