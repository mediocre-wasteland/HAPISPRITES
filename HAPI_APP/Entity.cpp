#include "Entity.h"



Entity::Entity(std::string &filename) : mSpriteName(filename)
{


}


Entity::~Entity()
{
}


void Entity::SetScaling(float floatx, float floaty)
{
	sprite->GetTransformComp().SetScaling({ floatx, floaty });
}

void Entity::SetRotation(float rotationF)
{
	sprite->GetTransformComp().SetRotation(rotationF);
}

void Entity::Render()
{
	sprite->Render(SCREEN_SURFACE);
}

bool Entity::LoadSprite()
{
	sprite = HAPI_Sprites.LoadSprite(mSpriteName);
	sprite->GetColliderComp().EnablePixelPerfectCollisions(true);

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

	if (xEntity == yEntity)
	{
		return false;
	}
	if ((xEntity == eSide::eNeutral) || (yEntity == eSide::eNeutral))
	{
		return false;
	}
	if (xEntity == eSide::eEnemy || yEntity == eSide::eEnemy)
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
	if (!CanCollide(Other)) // checks to see if the sides of the entities are the same
	{
		return;
	}

	CollisionInfo collision;

	if (sprite->CheckCollision(*Other.GetSprite(), &collision))
	{
		std::cout << "COLLIDING" << std::endl;
		isColliding = true;
		Other.isColliding = true;
	}
}
