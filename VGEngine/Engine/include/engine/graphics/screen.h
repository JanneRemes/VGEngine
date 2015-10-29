
#pragma once

#include "engine/utility/Vector2.h"

namespace vg
{
	namespace graphics
	{
		/**
		Static class that contains screen size and related functions
		*/
		class Screen
		{
			friend class GraphicsContext;

		public:
			/**
			@return screen size in pixels
			*/
			static vg::Vector2<int> getSize();

			/**
			@return screen size relative to transformComponent coordinates
			*/
			static vg::Vector2<int> getVirtualSize();

			/**
			@return screen width in pixels
			*/
			static int getX();

			/**
			@return screen height in pixels
			*/
			static int getY();

			/**
			Translates screen coordinates to world coordinates
			@param x input touch or mouse x coordinate
			@param y input touch or mouse y coordinate
			@return world coordinates
			*/
			static vg::Vector2<float> toWorld(float x, float y);

			/**
			Translates screen coordinates to world coordinates
			@param input touch or mouse coordinates
			@return world coordinates
			*/
			static vg::Vector2<float> toWorld(vg::Vector2<float> input);

		private:
			/**
			@param x width in pixels
			@param y height in pixels
			*/
			static void setSize(int x, int y);

			/**
			@param x width in pixels
			@param y height in pixels
			*/
			static void setVirtualSize(int x, int y);

			static vg::Vector2<int> mSize;			///< screen resolution in pixels
			static vg::Vector2<int> mVirtualSize;	///< used for scaling coordinates for different resolutions

		};
	}
}