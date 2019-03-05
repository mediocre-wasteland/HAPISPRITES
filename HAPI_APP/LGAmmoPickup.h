#pragma once
#include "PickUp.h"
#include "PlayerEntity.h"
class LGAmmoPickup
	: public PickUp
{
public:
	LGAmmoPickup();
	~LGAmmoPickup();
	void mBePickedUp(PlayerEntity player) { player.AddLGAmmo(mAmount);}
private:
	int mAmount;

};

