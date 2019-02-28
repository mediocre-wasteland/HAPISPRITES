#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
	for (auto &p : backgroundMap)
	{
		delete p.second;
	}

	for (auto &p : obstacleMap)
	{
		delete p.second;
	}
}

bool Map::Initialise()
{
	for (int i = 1; i < 11; i++)
	{
		std::string fileName = "Data\\Levels\\Level" + std::to_string(i) + ".txt";

		std::ifstream myFile(fileName);

		if (myFile.is_open())
		{
			myFile.close();
		}
		else
		{
			HAPI_Sprites.UserMessage("File could not be opened", "Error");
		}
	}

	return false;
}

void Map::CreateLevel()
{
	obstacleMap.clear();
	backgroundMap.clear();

	char line;
	std::string fileName = "Data\\Levels\\Level" + std::to_string(currentLevel) + ".txt";

	std::ifstream myFile(fileName);

	if (myFile.is_open())
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				myFile >> std::skipws >> line;

				float x = 64 * j;
				float y = 64 * i;

				if (line == 'S')
				{
					std::string key = "BG" + std::to_string(i) + std::to_string(j);

					backgroundMap[key] = new BackGroundEntity((std::string)"Data\\Sprites\\Sky.xml");

					backgroundMap[key]->SetPosition({ x,y });

					if (!backgroundMap[key]->LoadSprite())
					{
						HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
					}

				}

				if (line == 'B')
				{
					std::string key = "OB" + std::to_string(i) + std::to_string(j);

					obstacleMap[key] = new ObstacleEntity((std::string)"Data\\Sprites\\Brick.xml");

					obstacleMap[key]->SetPosition({ x,y });

					if (!obstacleMap[key]->LoadSprite())
					{
						HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
					}
				}
			}
		}

		myFile.close();
	}
	else
	{
		HAPI_Sprites.UserMessage("File could not be opened", "Error");
	}
}

void Map::Render()
{
	for (auto &p : obstacleMap)
	{
		p.second->Update();
		p.second->Render();
	}

	for (auto &p : backgroundMap)
	{
		p.second->Update();
		p.second->Render();
	}
}

void Map::MoveMap(eDirection moveDirection)
{
	switch (moveDirection)
	{
	case eDirection::eLeft:
		for (auto &p : obstacleMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x - 64, p.second->GetPosition().y });
		}
		for (auto &p : backgroundMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x - 64, p.second->GetPosition().y });
		}
		break;
	case eDirection::eRight:
		for (auto &p : obstacleMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x + 64, p.second->GetPosition().y });
		}
		for (auto &p : backgroundMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x + 64, p.second->GetPosition().y });
		}
		break;
	case eDirection::eUp:
		for (auto &p : obstacleMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y - 64 });
		}
		for (auto &p : backgroundMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y - 64 });
		}
		break;
	case eDirection::eDown:
		for (auto &p : obstacleMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y + 64 });
		}
		for (auto &p : backgroundMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y + 64 });
		}
		break;
	default:
		break;
	}
}
