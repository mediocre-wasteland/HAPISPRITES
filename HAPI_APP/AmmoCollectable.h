#pragma once
#include "Collectables.h"
#include "PlayerEntity.h"
class AmmoCollectable
	: public Entity
{
public:
	AmmoCollectable(std::string &filename);
	~AmmoCollectable();
	void Update() override { return; }// not used
	void Update(PlayerEntity* player);
	virtual eSide GetSide() const override final { return mSide; }
	virtual eDirection GetDirection() const override final { return  mDirection; }
private:
	int mAmount{ 12 };

};

