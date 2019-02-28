#pragma once
#include "PickUp.h"
#include "PlayerEntity.h"
class MoneyPickup :
	public PickUp
{
public:
	MoneyPickup();
	~MoneyPickup();
	void mBePickedUp(PlayerEntity player);
private:
	int mValue;
};

