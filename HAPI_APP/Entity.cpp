#include "Entity.h"



Entity::Entity(std::string &filename) : mSpriteName(filename)
{


}


Entity::~Entity()
{
}


void Entity::SetScaling(float floatx, float floaty)
{
	sprite->GetTransformComp().SetScaling({ 1.0f, 1.0f });
}

void Entity::SetRotation(float rotationF)
{
	sprite->GetTransformComp().SetRotation(0.3f);
}

void Entity::Render()
{
	sprite->Render(SCREEN_SURFACE);
}

bool Entity::LoadSprite()
{

	sprite = HAPI_Sprites.LoadSprite(mSpriteName);

	if (!sprite)
	{
		return false;
	}

	return true;
}

