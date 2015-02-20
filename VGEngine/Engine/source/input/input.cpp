#include "engine\input\input.h"
#include "engine\utility\logger.h"
/**
* Process the next input event.
*/
using namespace vg;
int32_t Input::mX;
int32_t Input::mY;
int32_t Input::engine_handle_input(android_app* app,AInputEvent* event) {
	//struct engine* engine = (struct engine*)app->userData;
	
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		Log("debug", "movement %d %d", AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
		mX = AMotionEvent_getX(event, 0);
		mY = AMotionEvent_getY(event, 0);
		/*
		engine->animating = 1;
		engine->state.x = AMotionEvent_getX(event, 0);
		engine->state.y = AMotionEvent_getY(event, 0);*/
		return 1;
	}
	return 0;
}

int32_t Input::getX()
{
	return mX;
}
int32_t Input::getY()
{
	return mY;
}

void Input::setX(int32_t x)
{
	mX = x;
}
void Input::setY(int32_t y)
{
	mY = y;
}