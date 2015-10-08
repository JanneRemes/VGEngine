
#pragma once

//#include "engine/platforms/android/android_native_app_glue.h"


namespace vg
{
	namespace input
	{
		class Input
		{
		public:
			static float getTouchX();
			static void setTouchX(float value);
			static float getTouchY();
			static void setTouchY(float value);
			static void setSensor(float x, float y, float z);
			static void setAngles(float x, float y, float z);
			static float getSensorX();
			static float getSensorY();
			static float getSensorZ();
			static bool getIsTouched();
			static void setIsTouched(bool value);
			static bool getIsTouchReleased();
			static void setIsTouchReleased(bool value);
			static void update();

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
