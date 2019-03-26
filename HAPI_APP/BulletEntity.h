#pragma once
#include "Entity.h"
#include "EnemyEntity.h"
class BulletEntity : 
	public Entity
{
public:
	BulletEntity(std::string &fileName);
	~BulletEntity();
	virtual void Update() override;
	void Update(std::vector<EnemyEntity> enemies);
private:
	int mSpeed{ 1 };
	VectorF mScreenSize;
};

