#include "Camera.h"


Camera::Camera(int height, int width) : mHeight(height), mWidth(width)
{
}


Camera::~Camera()
{
}

void Camera::MoveCamera(eDirection moveDirection, Map &mapIn, std::unordered_map <std::string, Entity*> &entityMapIn)
{
	switch (moveDirection)
	{
	case eDirection::eLeft:
		if ((mPosition.x + mWidth) < 3456)
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
	case eDirection::eUp:
		if ((mPosition.y + mHeight) < 3456)
		{
			mapIn.MoveMap(eDirection::eUp);
			for (auto &p : entityMapIn)
			{
				p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y - 2});
			}
			mPosition.y -= 2;
		}
		break;
	case eDirection::eDown:
		if (mPosition.y > 0)
		{
			mapIn.MoveMap(eDirection::eDown);
			for (auto &p : entityMapIn)
			{
				p.second->SetPosition({ p.second->GetPosition().x, p.second->GetPosition().y + 2 });
			}
			mPosition.y += 2;
		}
		break;
	default:
		break;
	}
}
