
#pragma once

#include "engine/platforms/android/android_native_app_glue.h"
#include <android/sensor.h>

namespace vg
{
	namespace input
	{
		class Input
		{
		public:
			static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);

			static float getTouchX();
			static float getTouchY();
			static float getSensorX();
			static float getSensorY();
			static float getSensorZ();
			static bool getIsTouched();
			static bool getIsTouchReleased();
			static void update();
			static void sensorEvent(ASensorEventQueue *queue);

		private:

			static bool isTouched;
			static bool isTouchReleased;
			static float mTouchX;
			static float mTouchY;
			static float mSensorX;
			static float mSensorY;
			static float mSensorZ;
			static float mAngleX;
			static float mAngleY;
			static float mAngleZ;
		};
	}
}
