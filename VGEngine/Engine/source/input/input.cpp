
#include "engine/input/input.h"
#include "engine/utility/logger.h"
#if defined (OS_ANDROID)
#include <android/sensor.h>

#include <android/looper.h>
#include "engine/platforms/android/android_native_app_glue.h"
#endif
/**
* Process the next input event.
*/
using namespace vg::input;

float Input::mTouchX = 0;
float Input::mTouchY = 0;
float Input::mSensorX = 0;
float Input::mSensorY = 0;
float Input::mSensorZ = 0;
float Input::mAngleX = 0;
float Input::mAngleY = 0;
float Input::mAngleZ = 0;
bool Input::isTouched = false;
bool Input::isTouchReleased = false;



float Input::getTouchX()
{
	return mTouchX;
}

float Input::getTouchY()
{
	return mTouchY;
}
float Input::getSensorX()
{
	return mSensorX;
}
float Input::getSensorY()
{
	return mSensorY;
}
float Input::getSensorZ()
{
	return mSensorZ;
}
bool Input::getIsTouched()
{
	return isTouched;
}
bool Input::getIsTouchReleased()
{
	return isTouchReleased;
}
void Input::update()
{
	if (isTouchReleased)
		isTouchReleased = false;
}

void Input::setTouchX(float value)
{
	mTouchX = value;
}
void Input::setTouchY(float value)
{
	mTouchY = value;
}
void Input::setIsTouched(bool value)
{
	isTouched = value;
}
void Input::setIsTouchReleased(bool value)
{
	isTouchReleased = value;
}
void Input::setSensor(float x, float y, float z)
{
	mSensorX = x;
	mSensorY = y;
	mSensorZ = z;
}
void Input::setAngles(float x, float y, float z)
{
	mAngleX = x;
	mAngleY = y;
	mAngleZ = z;
}