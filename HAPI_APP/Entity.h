#pragma once
#include <HAPISprites_Lib.h>
#include "HAPI_SPRITES/Shapes/Vector.h"

using namespace HAPISPACE;

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
	Entity(std::string &filename);
	HAPISPACE::VectorF GetPosition() const{ return mPosition; }
	void SetPosition(HAPISPACE::VectorF newPosition){ mOldPosition = mPosition;  mPosition = newPosition; }
	void SetScaling(float floatx, float floaty);
	void SetRotation(float rotationF);
	void Render();
	bool LoadSprite();
	bool IsAlive() { return mAlive; }
	virtual eSide GetSide() const = 0;
	virtual void Update() = 0;
	virtual ~Entity();
	virtual eDirection GetDirection() const = 0;
protected:
	std::shared_ptr<Sprite> sprite{ nullptr };
	std::string mSpriteName;
	float mSpeed;
	int mCurrentHealth;
	int mMaxHealth;
	bool mAlive;
	eSide mSide{ eSide::eNeutral };
	eDirection mDirection{ eDirection::eRight };

private:
	HAPISPACE::VectorF mPosition{ 0.f,0.f }; 
	HAPISPACE::VectorF mOldPosition{ 0.f ,0.f };
	
};


