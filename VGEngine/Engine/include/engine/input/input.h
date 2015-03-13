
#pragma once

#include "engine/android_native_app_glue.h"

namespace vg
{
	class Input
	{
	public:
		static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);

		static float getX();
		static float getY();
		static bool getIsTouched();
		static bool getIsTouchReleased();
		static void update();
	private:
		static bool isTouched;
		static bool isTouchReleased;
		static float mX;
		static float mY;
	};
}
