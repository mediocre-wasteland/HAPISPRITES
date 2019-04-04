#include "Entity.h"

Entity::Entity(std::string &fileName) : mSpriteName(fileName)
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
	if (mAlive)
	{
		sprite->Render(SCREEN_SURFACE);
	}
}

bool Entity::LoadSprite()
{
	sprite = HAPI_Sprites.LoadSprite(mSpriteName);
	constexpr int kMinAlphaForCollision{ 50};
	sprite->GetSpritesheet()->SetMinimumAlphaForCollision(kMinAlphaForCollision);
	sprite->GetSpritesheet()->AutoFitColliders();
	sprite->GetSpritesheet()->GenerateNormals();
	sprite->GetColliderComp().CalculateCollisionData(true);
	sprite->GetColliderComp().EnablePixelPerfectCollisions(true);
	sprite->GetTransformComp().SetPosition(mPosition);


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

	if ((xEntity != eSide::ePlayer && yEntity == eSide::eCollectable) || (xEntity == eSide::eCollectable && yEntity != eSide::ePlayer))
	{
		return false;
	}

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

	if ((xEntity == eSide::eBullet && yEntity != eSide::eEnemy) || (xEntity != eSide::eEnemy && yEntity == eSide::eBullet))
	{
		return false;
	}
	
	return true;
}

void Entity::CheckCollision(std::unordered_map < std::string, Entity* > &otherMap)
{
	myMap = otherMap;

	for (auto &Other : myMap)
	{
		//Check if both sprites are alive
		if (!IsAlive() || !Other.second->IsAlive())
		{
			continue;
		}

		//Check if both sides can collide (e.g. can collide if not on the same side)
		if (!CanCollide(*Other.second))
		{
			continue;
		}

		if (sprite->CheckCollision(*Other.second->GetSprite(), &collision))
		{
			isColliding = true;
			Other.second->isColliding = true;

			continue;
		}
	}

	return;
}

void Entity::MovementCollision()
{
	mPosition = sprite->GetTransformComp().GetPosition();

	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	//PHYSICS LOOP
	DWORD deltaTimeMS{ HAPI_Sprites.GetTime() - timeSinceLastMove };
	if (deltaTimeMS >= MoveTime)
	{
		deltaTimeS = 0.001f * deltaTimeMS;
		timeSinceLastMove = HAPI_Sprites.GetTime();


		if (!mIsOnGround)
		{
			Velocity.x = Velocity.x;
		}
		else
		{
			//JUMP IF ON GROUND
			if (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])
			{
				Velocity.y -= 10;
				mIsOnGround = false;
			}

			//MOVE LEFT / RIGHT
			if (mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT])
			{
				Velocity.x = 4;
			}
			else if (mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT])
			{
				Velocity.x = -4;
			}
			else
			{
				Velocity.x = 0;
			}
		}

		VectorF newPosition{ mPosition + Velocity };

		acceleration += force / mass;

		if (!mIsOnGround)
		{
			Velocity += (Gravity + acceleration) * deltaTimeS;
		}
		else
		{
			Velocity += acceleration * deltaTimeS;
		}

		//ANIMATION
		if (Velocity.x > 0 && Velocity.y == 0)
		{
			if (sprite->GetFrameSetName() != "RunRight")
			{
				mDirection = eDirection::eRight;
				sprite->SetAutoAnimate(10, true, "RunRight");
			}
		}

		if (Velocity.x < 0 && Velocity.y == 0)
		{
			if (sprite->GetFrameSetName() != "RunLeft")
			{
				mDirection = eDirection::eLeft;
				sprite->SetAutoAnimate(10, true, "RunLeft");
			}
		}

		if (Velocity.y < 0 && Velocity.x > 0)
		{
			if (sprite->GetFrameSetName() != "JumpRight")
			{
				mDirection = eDirection::eRight;
				sprite->SetAutoAnimate(3, true, "JumpRight");
			}
		}

		if (Velocity.y < 0 && Velocity.x < 0)
		{
			if (sprite->GetFrameSetName() != "JumpLeft")
			{
				mDirection = eDirection::eLeft;
				sprite->SetAutoAnimate(3, true, "JumpLeft");
			}
		}

		if (Velocity.x == 0 && Velocity.y == 0)
		{
			if (sprite->GetFrameSetName() != "Idle")
			{
				sprite->SetAutoAnimate(10, true, "Idle");
			}
		}

		VectorF dir{ newPosition - mOldPosition };
		dir.Normalize();

		bool done{ false };
		VectorF beforeCollisionPosition{ mOldPosition };

		if (!dir.IsZero())
		{
			beforeCollisionPosition = mPosition;
			mPosition += dir;
		}

		while (!done && !dir.IsZero())
		{
			mIsOnGround = false;

			sprite->GetTransformComp().SetPosition(mPosition);

			this->CheckCollision(myMap);

			if (this->isColliding)
			{
				Velocity = 0;
				mPosition = beforeCollisionPosition + collision.normal;

				mIsOnGround = true;

				if (collision.normal.y > 0)
				{
					mIsOnGround = false;
				}

				mLastCollidedCollisionInfo = collision;

				done = true;
			}
			else
			{
				if ((mPosition - newPosition).LengthSquared() < 72.0f)
				{
					mPosition = newPosition;
					done = true;
				}
				else
				{
					beforeCollisionPosition = mPosition;
					mPosition += dir;
				}
			}
		}

		if (mPosition.x < 0)
		{
			mPosition.x = 0;
			Velocity = 0;
		}
		
		if (mPosition.x + sprite->FrameWidth() >= SCREEN_SURFACE->Width())
		{
			mPosition.x = (float)(SCREEN_SURFACE->Width() - sprite->FrameWidth() - 1);
			Velocity = 0;
		}

		sprite->GetTransformComp().SetPosition(mPosition);

		mOldPosition = mPosition;
	}

	isColliding = false;
}