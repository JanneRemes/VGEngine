
#pragma once

#include <engine/utility/Vector2.h>

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
			@return camera focus position in pixels
			*/
			static Vector2<float> getPosition();

			/**
			Set camera focus position in pixels
			@param position in pixels
			*/
			static void setPosition(Vector2<float> position);

			/**
			Move camera focus position
			@param x position in pixels
			@param y position in pixels
			*/
			static void move(Vector2<float> change);

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

			

		private:

			static Vector2<float> mPosition;		///< camera focus position in pixels
			static float mZoom;					///< camera zoom level
			//static float mRotation;				///< camera rotation in degrees
			static float mLeft;					///< left border of screen
			static float mTop;					///< top border of screen
			static float mRight;				///< right border of screen
			static float mBottom;				///< bottom border of screen
		};
	}
}