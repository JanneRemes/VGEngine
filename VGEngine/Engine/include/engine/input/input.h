#pragma once
#include "engine/android_native_app_glue.h"
namespace vg
{
	class Input
	{
	public:
		static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);
		static int32_t getX();
		static int32_t getY();

		static void setX(int32_t x);
		static void setY(int32_t y);

	private:
		static int32_t mX;
		static int32_t mY;
	};

}