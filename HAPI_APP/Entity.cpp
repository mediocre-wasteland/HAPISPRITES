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
	//Render sprite entity if alive
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
	//Check which entities can collide
	eSide xEntity = GetSide();
	eSide yEntity = other.GetSide();

	//Make sure only the player can collide with collectables
	if ((xEntity != eSide::ePlayer && yEntity == eSide::eCollectable) || (xEntity == eSide::eCollectable && yEntity != eSide::ePlayer))
	{
		return false;
	}

	//Check if the entities are the same and prevent collision
	if (xEntity == yEntity)
	{
		return false;
	}

	//Check if one of the sides is neutral and prevent collison
	if ((xEntity == eSide::eNeutral) || (yEntity == eSide::eNeutral))
	{
		return false;
	}

	//Prevent the player from colliding with the bullet
	if ((xEntity == eSide::eBullet && yEntity == eSide::ePlayer) || (xEntity == eSide::ePlayer && yEntity == eSide::eBullet))
	{
		return false;
	}

	//Prevent the player from colliding with the cradle
	if ((xEntity == eSide::eCradle && yEntity == eSide::ePlayer) || (xEntity == eSide::ePlayer && yEntity == eSide::eCradle))
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

		//Check for a collision between sprites
		if (sprite->CheckCollision(*Other.second->GetSprite(), &collision) && collision.result == ECollisionResult::ePixelPerfectPass)
		{
			isColliding = true;
			Other.second->isColliding = true;

			continue;
		}
	}

	return;
}

void Entity::PlayerWalkMakeNoise()
{
	switch (RunNoise)
	{
	case 0:
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Running//run.wav");
		break;
	case 1:
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Running//run1.wav");
		break;
	case 2:
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Running//run2.wav");
		break;
	case 3:
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Running//run3.wav");
		break;
	case 4:
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Running//run4.wav");
		break;
	case 5:
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Running//run5.wav");
		break;
	case 6:
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Running//run6.wav");
		break;
	case 7:
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Running//run7.wav");
		break;
	case 8:
		RunNoise = 0;
		break;
	default:
		break;
	}
}

void Entity::PlayerMovementCollision()
{
	//Get the player position for camera movement
	mPosition = sprite->GetTransformComp().GetPosition();

	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	//Physics loop
	DWORD deltaTimeMS{ HAPI_Sprites.GetTime() - timeSinceLastUpdate };
	if (deltaTimeMS >= TimeBetweenUpdates)
	{
		deltaTimeS = 0.001f * deltaTimeMS;
		timeSinceLastUpdate = HAPI_Sprites.GetTime();

		if (!mIsOnGround)
		{
			Velocity.x = Velocity.x;

			//Allow the player to move left/right when in the air
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
			//Allow the player to jump when on the ground
			if (mKeyboardInput.scanCode['W'] || mKeyboardInput.scanCode[HK_SPACE] || mKeyboardInput.scanCode[HK_UP])
			{
				Velocity.y -= 10;
				if (Velocity.y < -9 && !isColliding)
				{
					HAPI_Sprites.PlaySound((std::string)"Data//Sounds//Jump.wav");
				}
			}

			//Allow the player to move left/right when on the ground
			if (mKeyboardInput.scanCode['D'] || mKeyboardInput.scanCode[HK_RIGHT])
			{
				PlayerWalkMakeNoise();
				RunNoise++;
				Velocity.x = 4;
			}
			else if (mKeyboardInput.scanCode['A'] || mKeyboardInput.scanCode[HK_LEFT])
			{
				PlayerWalkMakeNoise();
				RunNoise++;
				Velocity.x = -4;
			}
			else
			{
				Velocity.x = 0;
			}
		}

		VectorF newPosition{ mPosition + Velocity };

		acceleration += force / mass;

		//Test condition to prevent y velocity being huge on the first run through the loop.
		if (test == false)
		{
			deltaTimeS = 2;
			test = true;
		}

		//Apply gravity if the player is not on the ground
		if (!mIsOnGround)
		{
			Velocity += (Gravity + acceleration) * deltaTimeS;
		}
		else
		{
			Velocity += acceleration * deltaTimeS;
		}

		//Animation
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

		//Collision Checks
		VectorF dir{ newPosition - mOldPosition };
		dir.Normalize();

		bool done{ false };
		VectorF beforeCollisionPosition{ mOldPosition };

		if (!dir.IsZero())
		{
			beforeCollisionPosition = mPosition;
			mPosition += dir;
		}

		//Check if the player is moving up
		if (Velocity.y >= 0)
		{
			isTravellingUp = false;
		}
		else if (Velocity.y < 0 && mIsOnGround == false)
		{
			isTravellingUp = true;
		}

		//Check if the player is moving left or right
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

			//Check if the player is colliding
			if (this->isColliding)
			{
				Velocity = 0;

				//Move the player down if moving up and head collides
				if (isTravellingUp == true || mLastCollidedCollisionInfo.thisLocalPos.y < sprite->FrameHeight() / 4)
				{
					//Must match the max jump velocity
					collision.normal.y = 10;
				}
				else if (isTravellingUp == false)
				{
					mIsOnGround = true;
				}

				//Prevent player moving into blocks
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

		//Check if the player is off the screen
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

		isColliding = false;
	}
}

void Entity::GetPlayerPosFromWorld(HAPISPACE::VectorF playerPosition)
{
	this->playerPosition = playerPosition;
}