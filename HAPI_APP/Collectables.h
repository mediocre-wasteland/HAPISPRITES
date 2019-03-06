#pragma once

#include <HAPISprites_Lib.h>
#include <iostream>
#include "HAPI_SPRITES/Shapes/Vector.h"

using namespace HAPISPACE;

class Collectables
{
public:
	Collectables();
	~Collectables();
	virtual void mBePickedUp() = 0; // inherited pickups add what happens when picked up here
	HAPISPACE::VectorF GetPosition() const { return mPosition; } // returns position of pickup
	void SetPosition(HAPISPACE::VectorF newPosition) { mPosition = newPosition; } // sets the position to a new one
	void SetScaling(float floatx, float floaty); // sets scale of sprite
	void SetRotation(float rotationF); // sets rotation of sprite
	void Render(); // renders sprite
	bool LoadSprite(); // loads sprite
protected:
	std::shared_ptr<Sprite> sprite{ nullptr }; // pointer to the sprite data
	std::string mSpriteName; // name of the sprite
private:
	HAPISPACE::VectorF mPosition; // position of the pickup

};

