
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


float Input::mSensorX = 0;
float Input::mSensorY = 0;
float Input::mSensorZ = 0;
float Input::mAngleX = 0;
float Input::mAngleY = 0;
float Input::mAngleZ = 0;






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


void Input::update()
{

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