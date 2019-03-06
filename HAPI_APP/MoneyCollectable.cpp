#include "MoneyCollectable.h"



MoneyCollectable::MoneyCollectable()
{
}


MoneyCollectable::~MoneyCollectable()
{
}

void MoneyCollectable::mBePickedUp(PlayerEntity player)
{
	player.AddMoney(mValue);
}