#pragma once
#include <HAPISprites_Lib.h>
#include <iostream>
#include "HAPI_SPRITES/Shapes/Vector.h"

using namespace HAPISPACE;

enum class eSide
{
	ePlayer,
	eEnemy,
	eObstacle,
	eNeutral,
	eCradle,
	eCollectable
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
	Entity(std::string &filename);
	HAPISPACE::VectorF GetPosition() const{ return mPosition; }
	std::shared_ptr<Sprite> GetSprite() { return sprite; }
	void SetPosition(HAPISPACE::VectorF newPosition){ mOldPosition = mPosition;  mPosition = newPosition; }
	HAPISPACE::VectorF GetOldPosition() const { return mOldPosition; }
	void SetScaling(float floatx, float floaty);
	void SetRotation(float rotationF);
	void Render();
	bool LoadSprite();
	bool CanCollide(Entity& other);
	void CheckCollision(Entity& Other);
	bool IsAlive() { return mAlive; }
	virtual eSide GetSide() const = 0;
	virtual void Update() = 0;
	virtual ~Entity();
	virtual eDirection GetDirection() const = 0;

protected:
	std::shared_ptr<Sprite> sprite{ nullptr };
	std::string mSpriteName;
	float mSpeed{ 0 };
	int mCurrentHealth{ 0 };
	int mMaxHealth{ 0 };
	bool isColliding{ false };
	bool mAlive{false};
	CollisionInfo mCurrentCollisonInfo;
	CollisionInfo mLastCollidedCollisionInfo;
	eSide mSide{ eSide::eNeutral };
	eDirection mDirection{ eDirection::eRight };

private:
	HAPISPACE::VectorF mPosition{ 0.f,0.f }; 
	HAPISPACE::VectorF mOldPosition{ 0.f ,0.f };
};


