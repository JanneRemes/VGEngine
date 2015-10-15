
#pragma once
#include "engine/utility/vector2.h"
namespace vg
{
	namespace input
	{

		class Sensor
		{
		public:
			static void setSensor(float x, float y, float z);
			static void setAngles(float x, float y, float z);
			static float getSensorX();
			static float getSensorY();
			static float getSensorZ();
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
