
#pragma once

//#include "engine/platforms/android/android_native_app_glue.h"
namespace vg
{
	namespace input
	{
		class Input
		{
		public:
			static void setSensor(float x, float y, float z);
			static void setAngles(float x, float y, float z);
			static float getSensorX();
			static float getSensorY();
			static float getSensorZ();

			static void update();

		private:
			static float mSensorX;
			static float mSensorY;
			static float mSensorZ;
			static float mAngleX;
			static float mAngleY;
			static float mAngleZ;
		};
	}
}
