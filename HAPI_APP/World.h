#pragma once

#include <HAPISprites_Lib.h>
#include "HAPI_SPRITES/Shapes/Vector.h"
#include <unordered_map>

using namespace HAPISPACE;

class World
{
public:
	World();
	~World();

	bool Initialise();
	bool Play();

private:

	struct screenSpecs
	{
		HAPISPACE::Vector<int> screenDimensions = HAPISPACE::Vector<int>(1280, 800);
		HAPISPACE::BYTE* screenPointer{ nullptr };
	};

	screenSpecs gameScreenSpecs;
	//const HAPISPACE::KeyboardData &keyboardInput = HAPI_Sprites.GetKeyboardData();

	std::unordered_map <std::string, int*> entityMap;

	std::shared_ptr<Sprite> sprite{ nullptr };
	std::shared_ptr<Sprite> sprite2 { nullptr };


	bool LoadSprites();
	bool LoadEntities();
	bool LoadWorld();

	void Update();
	void Render();

	void GetInput();
	bool CheckCollision();
};

