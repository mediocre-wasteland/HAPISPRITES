#include "MoneyPickup.h"



MoneyPickup::MoneyPickup()
{
}


MoneyPickup::~MoneyPickup()
{
}

void MoneyPickup::mBePickedUp(PlayerEntity player)
{
	player.addMoney(mValue);
}