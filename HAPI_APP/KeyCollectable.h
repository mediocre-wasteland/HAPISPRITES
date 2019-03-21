#pragma once

#include "Collectables.h"
#include "PlayerEntity.h"

class KeyCollectable : public Collectables
{
public:
	KeyCollectable(std::string &fileName);
	~KeyCollectable();

	void Update(PlayerEntity* player) override;

private:

};

