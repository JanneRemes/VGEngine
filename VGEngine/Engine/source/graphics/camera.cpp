
#include "engine/graphics/camera.h"

using namespace vg;
using namespace vg::graphics;

// Default values
Vec2f Camera::mPosition = Vec2f(0,0);
float Camera::mZoom = 1.0f;
float Camera::mLeft = 0.0f;
float Camera::mTop = 0.0f;
float Camera::mRight = 0.0f;
float Camera::mBottom = 0.0f;
//float Camera::mRotation = 0.0f;

void Camera::reset()
{
	mPosition = Vec2f(0, 0);
	mZoom = 1.0f;
}

Vec2f Camera::getPosition()
{
	return mPosition;
}

void Camera::setPosition(Vec2f position)
{
	mPosition = position;
}

void Camera::setX(float x)
{
	mPosition.x = x;
}

void Camera::setY(float y)
{
	mPosition.y = y;
}

void Camera::move(Vec2f change)
{
	mPosition += change;
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

/*
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
*/