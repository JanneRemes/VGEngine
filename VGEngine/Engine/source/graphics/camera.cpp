
#include "engine/graphics/camera.h"

using namespace vg;
using namespace vg::graphics;

// Default values
Vector2<float> Camera::mPosition = Vector2<float>(0,0);
float Camera::mZoom = 1.0f;
float Camera::mLeft = 0.0f;
float Camera::mTop = 0.0f;
float Camera::mRight = 0.0f;
float Camera::mBottom = 0.0f;
//float Camera::mRotation = 0.0f;

void Camera::reset()
{
	mPosition = Vector2<float>(0, 0);
	mZoom = 1.0f;
}

Vector2<float> Camera::getPosition()
{
	return mPosition;
}

void Camera::setPosition(Vector2<float> position)
{
	mPosition = position;
}

void Camera::move(Vector2<float> change)
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