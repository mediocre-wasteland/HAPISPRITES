#include "Collectables.h"

Collectables::Collectables()
{

}

Collectables::~Collectables()
{

}

void Collectables::SetScaling(float floatx, float floaty)
{
	sprite->GetTransformComp().SetScaling({ floatx, floaty });
}

void Collectables::SetRotation(float rotationF)
{
	sprite->GetTransformComp().SetRotation(rotationF);
}

void Collectables::Render()
{
	sprite->Render(SCREEN_SURFACE);
}

bool Collectables::LoadSprite()
{

	sprite = HAPI_Sprites.LoadSprite(mSpriteName);

	if (!sprite)
	{
		return false;
	}

	return true;
}