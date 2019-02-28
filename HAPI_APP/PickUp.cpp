#include "PickUp.h"

PickUp::PickUp()
{

}

PickUp::~PickUp()
{

}

void PickUp::SetScaling(float floatx, float floaty)
{
	sprite->GetTransformComp().SetScaling({ floatx, floaty });
}

void PickUp::SetRotation(float rotationF)
{
	sprite->GetTransformComp().SetRotation(rotationF);
}

void PickUp::Render()
{
	sprite->Render(SCREEN_SURFACE);
}

bool PickUp::LoadSprite()
{

	sprite = HAPI_Sprites.LoadSprite(mSpriteName);

	if (!sprite)
	{
		return false;
	}

	return true;
}