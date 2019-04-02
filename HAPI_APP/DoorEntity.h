#pragma once

#include <HAPISprites_Lib.h>
#include "Entity.h"

class DoorEntity : public Entity
{
public:
	DoorEntity(std::string &fileName);
	~DoorEntity();

	void Update() override;

	eSide GetSide() const override final { return mSide; }
	eDirection GetDirection() const override final { return mDirection; }
};

