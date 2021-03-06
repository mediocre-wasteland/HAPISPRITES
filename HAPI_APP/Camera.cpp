#include "Camera.h"

Camera::Camera(int height, int width) : mHeight(height), mWidth(width)
{
}

Camera::~Camera()
{
}

//Return camera to the start when moving to a new level
void Camera::ResetCamera(Map& mapIn, std::unordered_map <std::string, Entity*>& entityMapIn)
{
	mPosition = { 0,0 };

	if (mapIn.GetLevel() == 5)
	{
		for (int i = 0; i < (mapIn.GetHeight() * 64) - 520; i++)
		{
			mapIn.MoveMap(eDirection::eUp);
			for (auto &p : entityMapIn)
			{
				p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x,  p.second->GetSprite()->GetTransformComp().GetPosition().y - 2 });
			}
			mPosition.y -= 2;
			i += 2;
		}
	}
}

//Move the camera by a set amount and in the correct direction depending on whether the level is vertical or horizontal
void Camera::MoveCamera(eDirection moveDirection, Map &mapIn, std::unordered_map <std::string, Entity*> &entityMapIn)
{
	if (mapIn.GetOrientation() == Horizontal)
	{
		switch (moveDirection)
		{
		case eDirection::eLeft:
			if ((mPosition.x + mWidth) < mapIn.GetWidth() * 64)
			{
				mapIn.MoveMap(eDirection::eLeft);

				for (auto &p : entityMapIn)
				{
					p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x - 2, p.second->GetSprite()->GetTransformComp().GetPosition().y });
				}

				mPosition.x += 2;
			}
			break;
		case eDirection::eRight:
			if (mPosition.x > 0)
			{
				mapIn.MoveMap(eDirection::eRight);

				for (auto &p : entityMapIn)
				{
					p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x + 2,  p.second->GetSprite()->GetTransformComp().GetPosition().y });
				}

				mPosition.x -= 2;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (moveDirection)
		{
		case eDirection::eUp:
			{
				mapIn.MoveMap(eDirection::eUp);
				for (auto &p : entityMapIn)
				{
					p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x,  p.second->GetSprite()->GetTransformComp().GetPosition().y - 2});
				}
				mPosition.y -= 2;
			}
			break;
		case eDirection::eDown:
			{
				mapIn.MoveMap(eDirection::eDown);
				for (auto &p : entityMapIn)
				{
					p.second->GetSprite()->GetTransformComp().SetPosition({ p.second->GetSprite()->GetTransformComp().GetPosition().x,  p.second->GetSprite()->GetTransformComp().GetPosition().y + 2 });
				}
				mPosition.y += 2;
			}
			break;
		default:
			break;
		}
	}

}
