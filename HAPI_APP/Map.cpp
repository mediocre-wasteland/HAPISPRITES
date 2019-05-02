#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
	for (auto &p : mBackgroundMap)
	{
		delete p.second;
	}
	mBackgroundMap.clear();

	for (auto &p : mObstacleMap)
	{
		delete p.second;
	}
	mObstacleMap.clear();

	for (auto &p : mCollectableMap)
	{
		delete p.second;
	}
	mCollectableMap.clear();
}

bool Map::Initialise()
{
	for (int i = 1; i < 6; i++)
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
	KillLevel();

	char line;
	std::string fileName = "Data\\Levels\\Level" + std::to_string(mCurrentLevel) + ".txt";

	std::fstream myFile(fileName);

	int width{ 0 }, height{ 0 };
	bool bWidth{ false };

	if (myFile.is_open())
	{
		for (int i = 0; i < 2000; i++)
		{
			char hLine;
			myFile >> std::skipws >> hLine;

			if (hLine == 'N' && bWidth == false)
			{
				width = i;
				bWidth = true;
				mLevelWidth = width;
			}

			if (hLine == 'N')
			{
				height++;
			}

			if (myFile.eof())
			{
				height--;
				mLevelHeight = height;
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

				int x = 64 * j;
				int y = 64 * i;

				switch (line)
				{
				case 'P':
					AddBackground("Palm", x, y);
					break;
				case 'W':
					AddBackground("Water", x, y);
					break;
				case 'B':
					AddObstacle("Brick", x, y);
					break;
				case 'C':
					AddObstacle("Cloud", x, y);
					break;
				case 'D':
					AddCollectable("Door", x, y, Door);
					break;
				case 'K':
					AddCollectable("KeyPlaceholder", x, y, Key);
					break;
				case 'A':
					AddCollectable("LoveGunAmmoPlaceholder", x, y, Ammo);
					break;
				case 'G':
					AddCollectable("Lighthouse", x, y + 64, Lighthouse); // Goal
					break;
				case 'M':
					AddCollectable("Cradle", x, y, Money);
					break;
				case 'I':
					spawnPos = {x,y};
					break;
				default:
					break;
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
	for (auto &p : mObstacleMap)
	{
		p.second->Update();
		p.second->Render();
	}

	for (auto &p : mBackgroundMap)
	{
		p.second->Update();
		p.second->Render();
	}

	for (auto &p : mCollectableMap)
	{
		p.second->Update();
		p.second->Render();
	}
}

eOrientation Map::GetOrientation()
{
	if (mLevelHeight > mLevelWidth)
	{
		return Vertical;
	}
	else
	{
		return Horizontal;
	}
}

void Map::MoveMap(eDirection moveDirection)
{

	switch (moveDirection)
	{
	case eDirection::eLeft:
		for (auto &p : mObstacleMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x - 2, p.second->GetSprite()->GetTransformComp().GetPosition().y });
		}
		for (auto &p : mBackgroundMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x - 2, p.second->GetSprite()->GetTransformComp().GetPosition().y });
		}
		for (auto &p : mCollectableMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x - 2, p.second->GetSprite()->GetTransformComp().GetPosition().y });
		}
		break;
	case eDirection::eRight:
		for (auto &p : mObstacleMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x + 2, p.second->GetSprite()->GetTransformComp().GetPosition().y });
		}
		for (auto &p : mBackgroundMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x + 2, p.second->GetSprite()->GetTransformComp().GetPosition().y });
		}
		for (auto &p : mCollectableMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x + 2, p.second->GetSprite()->GetTransformComp().GetPosition().y });
		}
		break;
	case eDirection::eUp:
		for (auto &p : mObstacleMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x, p.second->GetSprite()->GetTransformComp().GetPosition().y - 2 });
		}
		for (auto &p : mBackgroundMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x, p.second->GetSprite()->GetTransformComp().GetPosition().y - 2 });
		}
		for (auto &p : mCollectableMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x, p.second->GetSprite()->GetTransformComp().GetPosition().y - 2 });
		}
		break;
	case eDirection::eDown:
		for (auto &p : mObstacleMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x, p.second->GetSprite()->GetTransformComp().GetPosition().y + 2 });
		}
		for (auto &p : mBackgroundMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x, p.second->GetSprite()->GetTransformComp().GetPosition().y + 2 });
		}
		for (auto &p : mCollectableMap)
		{
			p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x, p.second->GetSprite()->GetTransformComp().GetPosition().y + 2 });
		}
		break;
	default:
		break;
	}
}

void Map::AddBackground(std::string fileName, int x, int y)
{
	std::string key = "BG" + std::to_string(y) + std::to_string(x);

	mBackgroundMap[key] = new BackGroundEntity((std::string)"Data\\Sprites\\" + fileName + ".xml");

	if (!mBackgroundMap[key]->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet : " + fileName, "ERROR");
	}

	mBackgroundMap[key]->GetSprite()->GetTransformComp().SetPosition({ (float)x,(float)y });
}

void Map::AddCollectable(std::string fileName, int x, int y, eColType type)
{
	std::string key = "CL" + std::to_string(y) + std::to_string(x);

	switch (type)
	{
	case Key:
		mCollectableMap[key] = new KeyCollectable((std::string)"Data\\Sprites\\" + fileName + ".xml");
		break;
	case Ammo:
		mCollectableMap[key] = new AmmoCollectable((std::string)"Data\\Sprites\\" + fileName + ".xml");
		break;
	case Money:
		mCollectableMap[key] = new MoneyCollectable((std::string)"Data\\Sprites\\" + fileName + ".xml");
		break;
	case Lighthouse:
		mCollectableMap[key] = new LightHouseGoal((std::string)"Data\\Sprites\\" + fileName + ".xml");
		break;
	case Door:
		mCollectableMap[key] = new DoorEntity((std::string)"Data\\Sprites\\" + fileName + ".xml");
		break;
	}

	if (!mCollectableMap[key]->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet : " + fileName , "ERROR");
	}

	mCollectableMap[key]->GetSprite()->GetTransformComp().SetPosition({ (float)x,(float)y });
}

void Map::AddObstacle(std::string fileName, int x, int y)
{
	std::string key = "OB" + std::to_string(y) + std::to_string(x);

	mObstacleMap[key] = new ObstacleEntity((std::string)"Data\\Sprites\\" + fileName + ".xml");

	if (!mObstacleMap[key]->LoadSprite())
	{
		HAPI_Sprites.UserMessage("Could not load spritesheet : " + fileName, "ERROR");
	}

	mObstacleMap[key]->GetSprite()->GetTransformComp().SetPosition({ (float)x,(float)y });
}

void Map::KillLevel()
{
	for (auto &p : mBackgroundMap)
	{
		delete p.second;
	}

	for (auto &p : mObstacleMap)
	{
		delete p.second;
	}

	for (auto &p : mCollectableMap)
	{
		delete p.second;
	}

	mBackgroundMap.clear();
	mObstacleMap.clear();
	mCollectableMap.clear();

}