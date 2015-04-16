
#include "engine/input/input.h"
#include "engine/utility/logger.h"


#include <android/looper.h>
/**
* Process the next input event.
*/
using namespace vg::Input;

float Input::mTouchX = 0;
float Input::mTouchY = 0;
float Input::mSensorX = 0;
float Input::mSensorY = 0;
float Input::mSensorZ = 0;
bool Input::isTouched = false;
bool Input::isTouchReleased = false;
int32_t Input::engine_handle_input(android_app* app, AInputEvent* event)
{
	//struct engine* engine = (struct engine*)app->userData;


	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		mTouchX = AMotionEvent_getX(event, 0);
		mTouchY = AMotionEvent_getY(event, 0);
		isTouched = true;
		Log("debug", "movement %f %f", mTouchX, mTouchY);
		if ((AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_UP)
		{
			Log("debug", "Released touch %d", 5);
			if (isTouched)
			{
				isTouched = false;
				isTouchReleased = true;
			}
		}
		/*
		engine->animating = 1;
		engine->state.x = AMotionEvent_getX(event, 0);
		engine->state.y = AMotionEvent_getY(event, 0);
		*/

		return 1;
	}

	return 0;
}
void Input::accelerometerEvent(ASensorEventQueue *queue)
{
	ASensorEvent event;
	while (ASensorEventQueue_getEvents(queue, &event, 1) > 0)
	{
		mSensorX = event.acceleration.x;
		mSensorY = event.acceleration.y;
		mSensorZ = event.acceleration.z;
		// Uncomment if needed
		//Log("DEBUG", "accelerometer: x=%f y=%f z=%f",event.acceleration.x, event.acceleration.y, event.acceleration.z);
	}
}
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