#pragma once
#include "Collectables.h"
#include "PlayerEntity.h"
class MoneyCollectable :
	public Collectables
{
public:
	MoneyCollectable();
	~MoneyCollectable();
	void mBePickedUp(PlayerEntity player);
private:
	int mValue;
};

