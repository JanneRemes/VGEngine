
#pragma once

#include <engine/utility/Vector2.h>

namespace vg
{
	namespace graphics
	{
		/**
		Static class that contains camera values needed for rendering
		*/
		class Camera
		{
		public:

			/**
			@return camera focus position in pixels
			*/
			static Vector2<int> getPosition();

			/**
			Set camera focus position in pixels
			@param position in pixels
			*/
			static void setPosition(Vector2<int> position);

			/**
			Move camera focus position
			@param x position in pixels
			@param y position in pixels
			*/
			static void move(Vector2<int> change);

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

			/**
			@param value top left visible point on screen
			*/
			static void setLeftTop(Vector2<float> value);
			
			/**
			@return top left visible point on screen
			*/
			static Vector2<float> getLeftTop();
			
			/**
			@param value bottom right visible point on screen
			*/
			static void setRightBottom(Vector2<float> value);

			/**
			@return bottom right visible point on screen
			*/
			static Vector2<float> getRightBottom();

		private:
			static Vector2<int> mPosition;		///< camera focus position in pixels
			static float mZoom;					///< camera zoom level
			//static float mRotation;				///< camera rotation in degrees
			static Vector2<float> mLeftTop;		///< top left corner of screen
			static Vector2<float> mRightBottom; ///< bottom right corner of screen
		};
	}
}