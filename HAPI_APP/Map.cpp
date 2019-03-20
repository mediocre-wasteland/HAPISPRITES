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

	std::fstream myFile(fileName);

	int width{ 0 }, height{ 0 };
	bool bWidth{ false };

	if (myFile.is_open())
	{
		for (int i = 0; i < 1000; i++)
		{
			char hLine;
			myFile >> std::skipws >> hLine;

			if (hLine == 'N' && bWidth == false)
			{
				width = i;
				bWidth = true;
			}

			if (hLine == 'N')
			{
				height++;
			}

			if (myFile.eof())
			{
				height--;
				break;
			}
		}

		myFile.clear();
		myFile.seekg(0, myFile.beg);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				myFile >> std::skipws >> line;

				if (line == 'N')
				{
					continue;
				}

				float x = 64 * j;
				float y = 64 * i;

				if (line == 'W')
				{
					std::string key = "BG" + std::to_string(i) + std::to_string(j);

					backgroundMap[key] = new BackGroundEntity((std::string)"Data\\Sprites\\Water.xml");

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


				if (line == 'C')
				{
					std::string key = "OB" + std::to_string(i) + std::to_string(j);

					obstacleMap[key] = new ObstacleEntity((std::string)"Data\\Sprites\\Cloud.xml");

					obstacleMap[key]->SetPosition({ x,y });

					if (!obstacleMap[key]->LoadSprite())
					{
						HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
					}
				}


				if (line == 'D')
				{
					std::string key = "OB" + std::to_string(i) + std::to_string(j);

					obstacleMap[key] = new ObstacleEntity((std::string)"Data\\Sprites\\Door.xml");

					obstacleMap[key]->SetPosition({ x,y });

					if (!obstacleMap[key]->LoadSprite())
					{
						HAPI_Sprites.UserMessage("Could not load spritesheet", "ERROR");
					}
				}
			}

			myFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
			p.second->SetPosition({ p.second->GetPosition().x - 2, p.second->GetPosition().y });
		}
		for (auto &p : backgroundMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x - 2, p.second->GetPosition().y });
		}
		break;
	case eDirection::eRight:
		for (auto &p : obstacleMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x + 2, p.second->GetPosition().y });
		}
		for (auto &p : backgroundMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x + 2, p.second->GetPosition().y });
		}
		break;
	case eDirection::eUp:
		for (auto &p : obstacleMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y - 2 });
		}
		for (auto &p : backgroundMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y - 2 });
		}
		break;
	case eDirection::eDown:
		for (auto &p : obstacleMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y + 2 });
		}
		for (auto &p : backgroundMap)
		{
			p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y + 2 });
		}
		break;
	default:
		break;
	}
}
