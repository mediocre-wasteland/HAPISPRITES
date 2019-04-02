#pragma once

#include "Collectables.h"
#include "PlayerEntity.h"
#include "Map.h"

class KeyCollectable : public Collectables
{
public:
	KeyCollectable(std::string &fileName);
	~KeyCollectable();

	void Update(PlayerEntity* player, Map& gameMap) override;

private:

};

