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

	if ((xEntity == eSide::eBullet && yEntity == eSide::eCollectable) || (xEntity == eSide::eCollectable && yEntity == eSide::eBullet))
	{
		return false;
	}
	if ((xEntity == eSide::eBullet && yEntity == eSide::ePlayer) || (xEntity == eSide::ePlayer && yEntity == eSide::eBullet))
	{
		return false;
	}
	
	return true;
}

void Entity::CheckCollision(std::unordered_map < std::string, Entity* > &otherMap)
{
	for (auto &Other : otherMap)
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

		if (sprite->CheckCollision(*Other.second->GetSprite(), &collision) && collision.result == ECollisionResult::ePixelPerfectPass)
		{
			isColliding = true;
			Other.second->isColliding = true;

			continue;
		}
	}

	return;
}

void Entity::PlayerMovementCollision()
{
	//GET THE PLAYER POSITION FOR CAMERA MOVEMENT
	mPosition = sprite->GetTransformComp().GetPosition();

	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	//PHYSICS LOOP
	DWORD deltaTimeMS{ HAPI_Sprites.GetTime() - timeSinceLastUpdate };
	if (deltaTimeMS >= TimeBetweenUpdates)
	{
		deltaTimeS = 0.001f * deltaTimeMS;
		timeSinceLastUpdate = HAPI_Sprites.GetTime();

		if (!mIsOnGround)
		{
			Velocity.x = Velocity.x;

			//ALLOW MOVE LEFT / RIGHT WHEN IN AIR
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
		else
		{
			//ALLOW PLAYER TO JUMP IF ON GROUND
			if (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])
			{
				Velocity.y -= 10;
				if (Velocity.y < -9 && !isColliding)
				{
					HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Jump.wav");
				}
			}

			//ALLOW MOVE LEFT / RIGHT WHEN ON GROUND
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

		if (test == false)
		{
			deltaTimeS = 2;
			test = true;
		}

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

		//COLLISION CHECKS
		VectorF dir{ newPosition - mOldPosition };
		dir.Normalize();

		bool done{ false };
		VectorF beforeCollisionPosition{ mOldPosition };

		if (!dir.IsZero())
		{
			beforeCollisionPosition = mPosition;
			mPosition += dir;
		}

		//CHECK IF PLAYER IS MOVING UP
		if (Velocity.y >= 0)
		{
			isTravellingUp = false;
		}
		else if (Velocity.y < 0 && mIsOnGround == false)
		{
			isTravellingUp = true;
		}

		bool isTravellingRight{ false };
		bool isTravellingLeft{ false };

		if (Velocity.x > 0)
		{
			isTravellingRight = true;
		}
		else if (Velocity.x < 0)
		{
			isTravellingLeft = true;
		}
		else
		{
			isTravellingRight = false;
			isTravellingLeft = false;
		}

		while (!done && !dir.IsZero())
		{
			mIsOnGround = false;

			sprite->GetTransformComp().SetPosition(mPosition);

			this->CheckCollision(myMap);

			if (this->isColliding)
			{
				Velocity = 0;

				if (isTravellingUp == true || mLastCollidedCollisionInfo.thisLocalPos.y < sprite->FrameHeight() / 4)
				{
					//Moves player down, must match the max jump velocity
					collision.normal.y = 10;
				}
				else if (isTravellingUp == false)
				{
					mIsOnGround = true;
				}

				if (isTravellingLeft && !mIsOnGround)
				{
					collision.normal.y = 5;
					collision.normal.x = 5;
				}

				if (isTravellingRight && !mIsOnGround)
				{
					collision.normal.y = 5;
					collision.normal.x = -5;
				}

				mPosition = beforeCollisionPosition + collision.normal;

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

		//CHECK IF PLAYER IS OFF SCREEN
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

		//isTravellingUp = false;
		isColliding = false;
	}
}