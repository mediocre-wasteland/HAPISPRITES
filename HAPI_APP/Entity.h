#pragma once

#include <iostream>
#include "HAPI_SPRITES/Shapes/Vector.h"
#include <HAPISprites_Lib.h>
#include <HAPISprites_UI.h>

using namespace HAPISPACE;
using namespace HAPI_UI_SPACE;

enum class eSide
{
	ePlayer,
	eEnemy,
	eObstacle,
	eNeutral,
	eCradle,
	eCollectable,
	eBullet
};

enum class eDirection
{
	eLeft,
	eRight,
	eUp,
	eDown
};

class Entity
{
public:
	Entity(std::string &fileName);

	virtual ~Entity();
	virtual void Update() = 0;
	virtual void Render();
	virtual eDirection GetDirection() const = 0;
	virtual eSide GetSide() const = 0;

	bool LoadSprite();
	bool CanCollide(Entity& other);
	bool IsAlive() { return mAlive; }
	bool isTravellingUp{ false };
	bool done{ false };

	void CheckCollision(std::unordered_map < std::string, Entity* >& otherMap);
	void SetScaling(float floatx, float floaty);
	void SetRotation(float rotationF);
	void PlayerWalkMakeNoise();
	void PlayerMovementCollision();
	void GetPlayerPosFromWorld(HAPISPACE::VectorF playerPosition);

	std::shared_ptr<Sprite> GetSprite() { return sprite; }

	CollisionInfo collision;

	std::unordered_map < std::string, Entity* > myMap;

	VectorF GetOldPosition() const { return mOldPosition; }
	VectorF beforeCollisionPosition{ mOldPosition };
	VectorF dir{ newPosition - mOldPosition };
	VectorF newPosition{ mPosition + Velocity };

protected:
	VectorF playerPosition;
	VectorF mPosition{ 64.f, 576.f };
	VectorF mOldPosition{ 0.f ,0.f };
	VectorF Gravity{ 0, 9.81f };
	VectorF Velocity{ 0, 0 };
	VectorF acceleration{ 0 };
	VectorF force{ 0, 0 };

	const DWORD TimeBetweenUpdates{ 20 };
	DWORD timeSinceLastUpdate{ HAPI_Sprites.GetTime() - 16 };

	bool mIsOnGround{ false };
	bool isColliding{ false };
	bool mAlive{ false };

	int mCurrentHealth{ 0 };
	int mMaxHealth{ 0 };
	int RunNoise{ 0 };
	float deltaTimeS{ 0 };
	float mass{ 1 };
	float mSpeed{ 0 };

	std::shared_ptr<Sprite> sprite{ nullptr };
	std::string mSpriteName;
	CollisionInfo mLastCollidedCollisionInfo;
	eSide mSide{ eSide::eNeutral };
	eDirection mDirection{ eDirection::eRight };

private:
	bool test = false;
};