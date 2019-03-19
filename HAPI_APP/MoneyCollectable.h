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
	void Update(PlayerEntity* player);
	virtual eSide GetSide() const override final { return mSide; }
	virtual eDirection GetDirection() const override final { return  mDirection; }
private:
	int mValue{ 250 };
};

