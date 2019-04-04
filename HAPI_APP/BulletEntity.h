#pragma once
#include "Entity.h"
#include "EnemyEntity.h"
class BulletEntity : 
	public Entity
{
public:
public:
	BulletEntity(std::string &fileName);
	~BulletEntity();
	virtual void Update() override {};
	void Update(std::vector<EnemyEntity*> enemies);
	void setPosition(VectorF newPos) { sprite->GetTransformComp().SetPosition(newPos); }

	virtual eSide GetSide() const override final { return mSide; }
	void SetDirection(eDirection newDirection) { mDirection = newDirection; }
	virtual eDirection GetDirection() const override final { return  mDirection; }
	void SetAliveStatus(bool isAlive) { mAlive = isAlive; }

private:
	int mSpeed{ 5 };
	VectorF mScreenSize;
};

