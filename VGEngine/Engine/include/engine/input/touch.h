
#pragma once
#include "engine/utility/vector2.h"
namespace vg
{
	namespace input
	{

		class Touch
		{
		public:
			static Vector2<float> getTouchPos();
			static void setTouchPos(Vector2<float> value);
			static bool getIsTouched();
			static void setIsTouched(bool value);
			static bool getIsTouchReleased();
			static void setIsTouchReleased(bool value);
			static void update();
		private:
			static bool isTouched;
			static bool isTouchReleased;
			static Vector2<float> touchPos;
		};
	}
}
