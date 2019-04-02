#pragma once
#include "Entity.h"
class PlayerEntity :
	public Entity
{
public:
	PlayerEntity(std::string &fileName);
	~PlayerEntity();

	virtual void Update() override;
	virtual void Render() override;

	void ShootLG(); 
	int GetMoneyAmount() { return mMoneyAmount; }
	int GetAmmoAmount() { return mLGAmmo; }

	virtual eSide GetSide() const override final{ return mSide; } 
	virtual eDirection GetDirection() const override final{ return  mDirection; }

	bool mHasKey{ false };
	void AddMoney(int amount);
	void AddLGAmmo(int amount);

private:

	///Collectables
	int mMoneyAmount{ 0 };
	bool mBankrupt{ false };
	int mLGAmmo{ 0 };
	int mLGMaxAmmo{ 96 };
};

