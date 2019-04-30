#pragma once

#include <HAPISprites_Lib.h>
using namespace HAPISPACE;
#include <HAPISprites_UI.h>
using namespace HAPI_UI_SPACE;

#include <iostream>
#include "HAPI_SPRITES/Shapes/Vector.h"


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
	bool LoadSprite();
	void CheckCollision(std::unordered_map < std::string, Entity* >& otherMap);

	virtual eDirection GetDirection() const = 0;
	virtual eSide GetSide() const = 0;

	bool CanCollide(Entity& other);

	std::shared_ptr<Sprite> GetSprite() { return sprite; }
	VectorF GetOldPosition() const { return mOldPosition; }

	bool IsAlive() { return mAlive; }

	void SetScaling(float floatx, float floaty);
	void SetRotation(float rotationF);

	CollisionInfo collision;

	void PlayerMovementCollision();

	std::unordered_map < std::string, Entity* > myMap;

	bool isTravellingUp{ false };
	bool done{ false };
	VectorF beforeCollisionPosition{ mOldPosition };
	VectorF dir{ newPosition - mOldPosition };
	VectorF newPosition{ mPosition + Velocity };

protected:

	VectorF mPosition{ 64.f, 576.f };
	VectorF mOldPosition{ 0.f ,0.f };

	const DWORD TimeBetweenUpdates{ 20 };
	DWORD timeSinceLastUpdate{ HAPI_Sprites.GetTime() - 16 };
	float deltaTimeS{ 0 };
	bool mIsOnGround{ false };
	VectorF Gravity{ 0, 9.81f };
	VectorF Velocity{ 0, 0 };
	VectorF acceleration{ 0 };
	float mass{ 1 };
	VectorF force{ 0, 0 };

	std::shared_ptr<Sprite> sprite{ nullptr };
	std::string mSpriteName;
	float mSpeed{ 0 };
	int mCurrentHealth{ 0 };
	int mMaxHealth{ 0 };
	bool isColliding{ false };
	bool mAlive{ false };
	CollisionInfo mLastCollidedCollisionInfo;
	eSide mSide{ eSide::eNeutral };
	eDirection mDirection{ eDirection::eRight };

private:


	bool test = false;
};


