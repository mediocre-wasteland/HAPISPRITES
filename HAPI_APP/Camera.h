#pragma once

#include <HAPISprites_Lib.h>
#include <unordered_map>
#include "Entity.h"
#include "Map.h"

using namespace HAPISPACE;

class Camera
{
public:
	Camera(int height, int width);
	~Camera();

	void Reset() { mPosition = { 0,0 }; };
	void MoveCamera(eDirection moveDirection, Map &mapIn, std::unordered_map <std::string, Entity*> &entityMapIn);

private:

	int mHeight{ 0 };
	int mWidth{ 0 };

	VectorF mPosition{0,0};
};

