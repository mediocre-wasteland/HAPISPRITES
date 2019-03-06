#include "Camera.h"


Camera::Camera(int height, int width) : mHeight(height), mWidth(width)
{
}


Camera::~Camera()
{
}

void Camera::MoveCamera(eDirection moveDirection, Map &mapIn)
{
	switch (moveDirection)
	{
	case eDirection::eLeft:
		if ((mPosition.x + mWidth) < 3456)
		{
			mapIn.MoveMap(eDirection::eLeft);
			mPosition.x += 2;
		}
		break;
	case eDirection::eRight:
		if (mPosition.x > 0)
		{
			mapIn.MoveMap(eDirection::eRight);
			mPosition.x -= 2;
		}
		break;
	case eDirection::eUp:
		if ((mPosition.y + mHeight) < 3456)
		{
			mapIn.MoveMap(eDirection::eUp);
			mPosition.y -= 2;
		}
		break;
	case eDirection::eDown:
		if (mPosition.y > 0)
		{
			mapIn.MoveMap(eDirection::eDown);
			mPosition.y += 2;
		}
		break;
	default:
		break;
	}
}
