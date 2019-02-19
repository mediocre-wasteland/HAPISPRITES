#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
	for (auto &p : entityMap)
	{
		delete p.second;
	}
}

bool Map::Initialise()
{
	return false;
}

void Map::CreateLevel(int levelNum)
{
	char line;
	std::string fileName = "Data\\Levels\\Level" + std::to_string(levelNum) + ".txt";

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

					entityMap[key] = new BackGroundEntity((std::string)"Data\\Sprites\\Sky.xml");

					entityMap[key]->SetPosition({ x,y });

					if (!entityMap[key]->LoadSprite())
					{
						HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
					}

				}

				if (line == 'B')
				{
					std::string key = "OB" + std::to_string(i) + std::to_string(j);

					entityMap[key] = new ObstacleEntity((std::string)"Data\\Sprites\\Brick.xml");

					entityMap[key]->SetPosition({ x,y });

					if (!entityMap[key]->LoadSprite())
					{
						HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
					}
				}

				std::cout << x << " " << y << std::endl;
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
	for (auto &p : entityMap)
	{
		p.second->Update();
		p.second->Render();
	}
}
