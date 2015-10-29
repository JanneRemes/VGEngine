
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

		/**
		Class for checking where and when mouse is clicked
		*/
		class Mouse
		{
		public:
			/**
			@return Returns whether the mouse is being pressed
			*/
			static bool isKeyPressed(MOUSE_KEY key);

			/**
			@return Returns the mouse position
			*/
			static vg::Vector2<float> getPos();
			
		};
	}
}
