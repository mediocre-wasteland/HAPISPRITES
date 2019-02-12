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
	HAPISPACE::VectorF GetPosition() const{ return mPosition; }
	void SetPosition(HAPISPACE::VectorF newPosition){ mOldPosition = mPosition;  mPosition = newPosition; }
	void Render();
	bool isAlive() { return mAlive; }
	virtual eSide getSide() const = 0;
	virtual void Update() = 0;
	virtual ~Entity();
	virtual eDirection getDirection() const = 0;
protected:
	float mSpeed;
	int mCurrentHealth;
	int mMaxHealth;
	bool mAlive;
	eSide mSide { eSide::eNeutral };
	eDirection mDirection{ eDirection::eRight };

private:
	HAPISPACE::VectorF mPosition{ 0.f,0.f }; 
	HAPISPACE::VectorF mOldPosition{ 0.f ,0.f };
	
};


