
#include "engine/input/sensor.h"

/**
* Process the next input event.
*/
using namespace vg::input;


float Sensor::mSensorX = 0;
float Sensor::mSensorY = 0;
float Sensor::mSensorZ = 0;
float Sensor::mAngleX = 0;
float Sensor::mAngleY = 0;
float Sensor::mAngleZ = 0;






float Sensor::getSensorX()
{
	return mSensorX;
}
float Sensor::getSensorY()
{
	return mSensorY;
}
float Sensor::getSensorZ()
{
	return mSensorZ;
}



void Sensor::setSensor(float x, float y, float z)
{
	mSensorX = x;
	mSensorY = y;
	mSensorZ = z;
}
void Sensor::setAngles(float x, float y, float z)
{
	mAngleX = x;
	mAngleY = y;
	mAngleZ = z;
}