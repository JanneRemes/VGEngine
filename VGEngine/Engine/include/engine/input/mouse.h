
#pragma once

#include "engine/utility/vec2f.h"

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
			static vg::Vec2f getPos(bool relativeToCamera = true);

			/**
			@return normalized vector from center of screen pointing towards input position
			*/
			static vg::Vec2f fromCenter();

			/**
			Saves mouse button states
			*/
			static void update();

		private:
			//not visible to end user
			static bool keyDown(MOUSE_KEY key);
			
		};
	}
}
