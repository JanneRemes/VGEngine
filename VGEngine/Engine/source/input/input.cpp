
#include "engine/input/input.h"
#include "engine/utility/logger.h"

/**
* Process the next input event.
*/
using namespace vg;

float Input::mX = 0;
float Input::mY = 0;
bool Input::isTouched = false;
bool Input::isTouchReleased = false;
int32_t Input::engine_handle_input(android_app* app, AInputEvent* event)
{
	//struct engine* engine = (struct engine*)app->userData;


	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		mX = AMotionEvent_getX(event, 0);
		mY = AMotionEvent_getY(event, 0);
		isTouched = true;
		Log("debug", "movement %f %f", mX, mY);
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

float Input::getX()
{
	return mX;
}

float Input::getY()
{
	return mY;
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