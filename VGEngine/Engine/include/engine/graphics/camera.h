
#pragma once

#include "engine/utility/vec2f.h"

namespace vg
{
	class RenderSystem;

	namespace graphics
	{
		/**
		Static class that contains camera values needed for rendering
		*/
		class Camera
		{
		friend class Screen;
		friend class vg::RenderSystem;

		public:

			/**
			Reset Camera to it's default values
			*/
			static void reset();

			/**
			@return camera focus position in pixels
			*/
			static Vec2f getPosition();

			/**
			Set camera focus position in pixels
			@param position in pixels
			*/
			static void setPosition(Vec2f position);

			/**
			@param x new horizontal position
			*/
			static void setX(float x);

			/**
			@param y new vertical position
			*/
			static void setY(float y);

			/**
			Move camera focus position
			@param x position in pixels
			@param y position in pixels
			*/
			static void move(Vec2f change);

			/**
			@return camera zoom level
			*/
			static float getZoom();

			/**
			Set camera zoom
			@param scale must be greater than zero
			*/
			static void setZoom(float zoom);

			/**
			Zoom the camera
			@param change added to zoom
			*/
			static void zoom(float change);

			/*
			@return camera rotation
			*/
			//static float getRotation();

			/*
			Set camera rotation
			@param rotation in degrees
			*/
			//static void setRotation(float rotation);

			/*
			Rotate camera position
			@param change rotation in degrees
			*/
			//static void rotate(float change);

		private:
			static Vec2f mPosition;				///< camera focus position in pixels
			static float mZoom;					///< camera zoom level
			static float mLeft;					///< left border of screen
			static float mTop;					///< top border of screen
			static float mRight;				///< right border of screen
			static float mBottom;				///< bottom border of screen
			/*static float mRotation;			///< camera rotation in degrees*/
		};
	}
}