#pragma once
#include "Entity.h"
#include "BulletEntity.h"
class PlayerEntity :
	public Entity
{
public:
	PlayerEntity(std::string &fileName);
	~PlayerEntity();

	void Update() override;
	void Render() override;

	void ShootLG(); 
	int GetMoneyAmount() { return mMoneyAmount; }
	int GetAmmoAmount() { return mLGAmmo; }

	void BulletVectorPushBack(BulletEntity* bullet) { mBullets.push_back(bullet); }
	void BulletVectorClear() { mBullets.clear(); }

	eSide GetSide() const override final{ return mSide; } 
	eDirection GetDirection() const override final{ return  mDirection; }

	bool mHasKey{ false };
	void AddMoney(int amount);
	void AddLGAmmo(int amount);

private:

	///Collectables
	int mMoneyAmount{ 0 };
	bool mBankrupt{ false };
	int mLGAmmo{ 12 };
	int mLGMaxAmmo{ 96 };

	///Shooting
	std::vector<BulletEntity*> mBullets;
	int updatesSinceLGlastFired = 100; // how many updates have passed since the love gun was last fired
	int LGCooldownUpdates = 100; // how many updates after firing the lovegun before you can fire again
};

