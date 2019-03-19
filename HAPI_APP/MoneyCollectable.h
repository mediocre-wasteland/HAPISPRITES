#pragma once
#include "Collectables.h"
#include "PlayerEntity.h"
class MoneyCollectable :
	public Entity
{
public:
	MoneyCollectable(std::string &filename);
	~MoneyCollectable();
	void Update() override { return; }// not used
	void Update(PlayerEntity* player);// main update used to check if the collectable is collected
	virtual eSide GetSide() const override final { return mSide; }
	virtual eDirection GetDirection() const override final { return  mDirection; }
private:
	int mValue{ 250 }; // the amount of money this will grant if collided with
};

