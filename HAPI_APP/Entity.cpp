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

bool Entity::CanCollide(Entity & other)
{
	eSide xEntity = GetSide();
	eSide yEntity = other.GetSide();
	if (xEntity == yEntity || yEntity == xEntity)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

void Entity::CheckCollision(Entity & Other)
{
	if (!IsAlive() || !Other.IsAlive())
	{
		return;
	}
	if (!CanCollide(Other))
	{
		return;
	}

	if (sprite->CheckCollision(*Other.GetSprite()))
	{
		isColliding = true;
		std::cout << "COLLIDING" << std::endl;
	}
	else
	{
		isColliding = false;
		std::cout << "NOT COLLIDING" << std::endl;
	}
}
