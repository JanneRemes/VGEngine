
#pragma once
#include "engine/utility/vector2.h"
namespace vg
{
	namespace input
	{
		enum MOUSE_KEY{
			LEFT,
			RIGHT,
			MIDDLE
			
		};
		class Mouse
		{
		public:
			static bool isKeyPressed(MOUSE_KEY key);
			static vg::Vector2<float> getMousePos();
			
		};
	}
}
