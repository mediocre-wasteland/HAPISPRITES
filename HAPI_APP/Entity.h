#pragma once
#include <HAPISprites_Lib.h>
#include "HAPI_SPRITES/Shapes/Vector.h"
enum class eSide
{
	ePlayer,
	eEnemy,
	eObstacle,
	eNeutral,
	eCradle

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
	Entity();
	virtual ~Entity();

	HAPISPACE::VectorF GetPosition() const{ return mPosition; }
	void SetPosition(HAPISPACE::VectorF newPosition){ mOldPosition = mPosition;  mPosition = newPosition; }

	virtual void Update() = 0;
	void Render();

	bool IsAlive() { return mAlive; }
	virtual eSide GetSide() const = 0;
	virtual eDirection GetDirection() const = 0;

	float GetPosX() { return mPosition.x; }
	float GetPosY() { return mPosition.y; }

protected:
	float mSpeed;
	int mCurrentHealth;
	int mMaxHealth;
	bool mAlive;
	eSide mSide { eSide::eNeutral };
	eDirection mDirection{ eDirection::eRight };
	//TODO needs to hold its own sprite to call Sprite->Render
	HAPISPACE::VectorF mPosition{ 0.f,0.f };

private:
	HAPISPACE::VectorF mOldPosition{ 0.f ,0.f };
	
};


