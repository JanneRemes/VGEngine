
#pragma once
#include "engine/utility/vector2.h"
namespace vg
{
	namespace input
	{
		/**
		Class used to handle actions regarding the touch screen
		*/
		class Touch
		{
		public:
			/**
			@return Returns the position of the touch
			*/
			static Vector2<float> getTouchPos();

			/**
			Sets the position of the touch with the given value
			@param value Given touches position
			*/
			static void setTouchPos(Vector2<float> value);

			/**
			@return Returns whether screen is touched
			*/
			static bool getIsTouched();

			/**
			Sets screens touch with value
			@param value True or false depending what is set
			*/
			static void setIsTouched(bool value);

			/**
			@return Returns whether touch is being released from the touch screen
			*/
			static bool getIsTouchReleased();

			/**
			Sets whether touch is being released or not
			*/
			static void setIsTouchReleased(bool value);

			/**
			Updates touches
			*/
			static void update();
		private:
			static bool isTouched;			///< Is touched
			static bool isTouchReleased;	///< Is touch being released
			static Vector2<float> touchPos;	///< Touch position in Vector2
		};
	}
}
