#pragma once
#include "Entity.h"

class BulletEntity : public Entity
{
public:
public:
	BulletEntity(std::string &fileName);
	~BulletEntity();

	virtual void Update();
	virtual eSide GetSide() const override final { return mSide; }
	virtual eDirection GetDirection() const override final { return  mDirection; }

	void setPosition(VectorF newPos) { sprite->GetTransformComp().SetPosition(newPos); }
	void SetDirection(eDirection newDirection) { mDirection = newDirection; }
	void SetAliveStatus(bool isAlive) { mAlive = isAlive; }

private:
	int mSpeed{ 5 };

	VectorF mScreenSize;
};

