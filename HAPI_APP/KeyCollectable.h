#pragma once
#include "Entity.h"

class KeyCollectable : public Entity
{
public:
	KeyCollectable(std::string &filename);
	~KeyCollectable();

	virtual void Update() override;
	virtual eSide GetSide() const override final { return mSide; }
	virtual eDirection GetDirection() const override final { return  mDirection; }

private:

};

