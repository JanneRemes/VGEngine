
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
			@return Returns whether the mouse is being pressed once or not
			*/
			static bool isKeyPressed(MOUSE_KEY key);

			/**
			@return Returns whether the mouse is down or not
			*/
			static bool isKeyDown(MOUSE_KEY key);

			/**
			@return Returns the mouse position translated to world coordinates
			*/
			static vg::Vector2<float> getPos(bool relativeToCamera = true);

			/**
			@return normalized vector from center of screen pointing towards input position
			*/
			static vg::Vector2<float> fromCenter();
			
		};
	}
}
