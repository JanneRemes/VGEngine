
#pragma once

#include "engine/utility/Vector2.h"
#include "engine/utility/color.h"

namespace vg
{
	namespace graphics
	{
		/**
		Static class that contains two different resolutions and related functions. Real 
		resolution is the devices screen or window size in pixels. Virtual resolution 
		is the screen or window size in TransformComponents coordinate units. The virtual 
		one should be used whenever possible to make games resolution independent.
		*/
		class Screen
		{
			friend class GraphicsContext;

		public:
			/**
			Get virtual resolution that is used to make rendering independent of resolution
			@return screen size in TransformComponent coordinate units
			*/
			static vg::Vector2<int> getSize();

			/**
			Use getSize() instead whenever possible! Returns the real screen resolution in pixels.
			@return screen size in pixels
			*/
			static vg::Vector2<int> getRealSize();

			/**
			Get virtual screen width that is used to make rendering independent of resolution
			@return screen width in TransformComponent coordinate units
			*/
			static int getX();

			/**
			Get virtual screen height that is used to make rendering independent of resolution
			@return screen height in TransformComponent coordinate units
			*/
			static int getY();

			/**
			Set virtual resolution that is used to make rendering independent of resolution.
			@param x width in TransformComponent coordinate units
			@param y height in TransformComponent coordinate units
			*/
			static void setSize(int x, int y);

			/**
			Translates virtual screen coordinates to world coordinates
			@param x input touch or mouse x coordinate
			@param y input touch or mouse y coordinate
			@return world coordinates
			*/
			static vg::Vector2<float> toWorld(float x, float y);

			/**
			Translates virtual screen coordinates to world coordinates
			@param input touch or mouse coordinates
			@return world coordinates
			*/
			static vg::Vector2<float> toWorld(vg::Vector2<float> input);

			/**
			Translates point in screen coordinates to virtual resolution coordinates
			@param input point in real resolution
			@return point in virtual resolution
			*/
			static vg::Vector2<float> realToVirtual(Vector2<float> input);

			/**
			Translates point in screen coordinates to virtual resolution coordinates
			@param x,y point in real resolution
			@return point in virtual resolution
			*/
			static vg::Vector2<float> realToVirtual(float x, float y);

			/**
			Set glClearColor value
			*/
			static void setColor(vg::Color color);

			/**
			@return color for glClearScreen
			*/
			static vg::Color getColor();

		private:
			/**
			Set actual screen size in pixels
			@param x width in pixels
			@param y height in pixels
			*/
			static void setRealSize(int x, int y);

			static vg::Vector2<int> mSize;		///< Virtual resolution that is used to make rendering independent of resolution.
			static vg::Vector2<int> mRealSize;	///< Screen resolution in pixels
			static vg::Color mColor;			///< color used for glClearScreen
		};
	}
}