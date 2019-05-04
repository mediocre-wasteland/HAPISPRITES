#pragma once

#include "Entity.h"
#include "BulletEntity.h"

class PlayerEntity : public Entity
{
public:
	PlayerEntity(std::string &fileName);
	~PlayerEntity();

	void Update() override;
	void Render() override;
	void ShootLG(); 
	void AddMoney(int amount);
	void AddLGAmmo(int amount);
	void BulletVectorPushBack(BulletEntity* bullet) { mBullets.push_back(bullet); }
	void BulletVectorClear() { mBullets.clear(); }

	int GetMoneyAmount() { return mMoneyAmount; }
	int GetAmmoAmount() { return mLGAmmo; }

	bool mHasKey{ false };

	eSide GetSide() const override final{ return mSide; } 
	eDirection GetDirection() const override final{ return  mDirection; }

private:
	int mMoneyAmount{ 0 }; //MONEY HAS BEEN REPLACED WITH BABIES
	int mLGAmmo{ 12 };
	int mLGMaxAmmo{ 96 };

	std::vector<BulletEntity*> mBullets;

	int updatesSinceLGlastFired = 100;
	int LGCooldownUpdates = 100;
};

