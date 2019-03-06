#pragma once
#include "Collectables.h"
#include "PlayerEntity.h"
class AmmoCollectable
	: public Collectables
{
public:
	AmmoCollectable();
	~AmmoCollectable();
	void mBePickedUp(PlayerEntity player) { player.AddLGAmmo(mAmount); }
private:
	int mAmount;

};

