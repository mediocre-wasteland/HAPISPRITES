#pragma once

#include <HAPISprites_Lib.h>
#include "HAPI_SPRITES/Shapes/Vector.h"
#include <unordered_map>
#include "Player.h"

using namespace HAPISPACE;

class World
{
public:
	World();
	~World();

	bool Initialise();
	bool Play();

private:

	HAPISPACE::Vector<int> screenDimensions = HAPISPACE::Vector<int>(1280, 800);

	std::unordered_map <std::string, int*> entityMap;

	std::shared_ptr<Sprite> sprite{ nullptr };
	std::shared_ptr<Sprite> sprite2 { nullptr };
	Player mainPlayer;

	bool LoadSprites();
	bool LoadEntities();
	bool LoadWorld();

	void Update();
	void Render();

	bool CheckCollision();
};

