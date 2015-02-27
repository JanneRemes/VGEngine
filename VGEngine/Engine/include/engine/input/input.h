
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
	private:
		static float mX;
		static float mY;
	};
}
