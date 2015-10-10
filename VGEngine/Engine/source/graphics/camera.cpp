
#include <engine\graphics\camera.h>

using namespace vg;
using namespace vg::graphics;

// Default values
Vector2<int> Camera::mPosition = Vector2<int>(0,0);
float Camera::mZoom = 1.0f;
float Camera::mRotation = 0.0f;

Vector2<int> Camera::getPosition()
{
	return mPosition;
}

void Camera::setPosition(Vector2<int> position)
{
	mPosition = position;
}

void Camera::move(Vector2<int> change)
{
	mPosition += change;
}

float Camera::getRotation()
{
	return mRotation;
}

void Camera::setRotation(float rotation)
{
	mRotation = rotation;
}

void Camera::rotate(float change)
{
	mRotation += change;
}

float Camera::getZoom()
{
	return mZoom;
}

void Camera::setZoom(float zoom)
{
	if (zoom < 0.0f)
		zoom = 0.0f;
	mZoom = zoom;
}

void Camera::zoom(float change)
{
	mZoom += change; 
	if (mZoom < 0.0f)
		mZoom = 0.0f;
}
