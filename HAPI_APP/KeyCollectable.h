#pragma once
#include "Entity.h"
#include "PlayerEntity.h"

class KeyCollectable : public Entity
{
public:
	KeyCollectable(std::string &filename);
	~KeyCollectable();

	virtual void Update() { return; }
	void Update(PlayerEntity* player);
	virtual eSide GetSide() const override final { return mSide; }
	virtual eDirection GetDirection() const override final { return  mDirection; }

private:

};

