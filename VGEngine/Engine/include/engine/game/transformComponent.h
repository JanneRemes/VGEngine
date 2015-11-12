
#pragma once

#include "engine/game/component.h"
#include "engine/utility/vec2f.h"

namespace vg
{

	/**
	Component for managing gameObject by moving, rotating or scaling
	*/
	class TransformComponent :public Component
	{
	public:
		/**
		Layers for rendering. Sprites on higher layers are drawn on top of lower ones.
		BOTTOM	recommended for backgrounds
		MIDDLE	default value
		TOP		recommended for user interface
		*/
		enum Layer
		{
			BOTTOM = 0, // 1 - 9 999
			LOW,		// 10 000 - 19 999
			MIDDLE,		// 20 000 - 79 999
			HIGH,		// 80 000 - 89 999
			TOP			// 90 000 - 100 000
		};


		TransformComponent();
		TransformComponent(const TransformComponent &transform);
		/**
		@param position position of upper left corner in pixels
		@param size width and lenght of the sprite in pixels
		@param rotation angle of rotation clockwise
		@param origin offset of origin in pixels from upper left corner
		@param layer higher layers are drawn over lower ones
		@param useCamera true if the position is affected by camera
		*/
		TransformComponent(vg::Vector2<float> position, vg::Vector2<float> size,
			float rotation, vg::Vector2<float> origin = vg::Vector2<float>(0, 0),
			Layer layer = MIDDLE, bool useCamera = true);

		/**
		@param position position of upper left corner in pixels
		@param size width and lenght of the sprite in pixels
		@param rotation angle of rotation clockwise
		@param origin offset of origin in pixels from upper left corner
		*/
		TransformComponent(vg::Vec2f position, vg::Vec2f size, float rotation = 0.0f, vg::Vec2f origin = vg::Vec2f());

		~TransformComponent();

		/**
		@return local position (only taking into account this component´s position not parent´s position)
		*/
		vg::Vector2<float> getLocalPosition();

		/**
		@return world position (adds parent gameobject´s position to this components local position)
		*/
		vg::Vector2<float> getWorldPosition();
		
		/**
		Set position value to be used on draw calls.
		*/
		void setPosition(const vg::Vector2<float> position);

		/**
		Set position value to be used on draw calls.
		*/
		void setPosition(const Vec2f position);

		/**
		Add to the position value to be used on draw calls.
		*/
		void move(vg::Vector2<float> change);

		/**
		@return size in pixels
		*/
		vg::Vector2<float> getSize();


		/**
		Set position value to be used on draw calls.
		*/
		void setSize(const vg::Vector2<float> size);

		/**
		@return rotation in degrees
		*/
		float getLocalRotation();
		/**
		stuff
		*/
		float getWorldRotation();
		/**
		Set rotation value to be used on draw calls.
		*/
		void setRotation(float rotation);

		/**
		Add to the rotation value
		*/
		void rotate(float rotatation);

		/**
		@return real layer value ranging from 0 to 8000000.
		*/
		float getLayer();

		/**
		@param layer range
		*/
		void setLayer(Layer layer);

		/**
		@return origin offset
		*/
		vg::Vector2<float> getOrigin();

		/**
		Set origin offset.
		*/
		void setOrigin(const vg::Vector2<float> origin);

		/**
		@param value true if the position is affected by camera
		*/
		void setUsingCamera(bool value);

		/**
		@return true if the position is affected by camera
		*/
		bool getUsingCamera();

		/**
		@return true if the point is inside this TransformComponent
		*/
		bool contains(Vector2<float> point);

	private:
		vg::Vector2<float> mPosition;			///< Position of top left corner in pixels.
		vg::Vector2<float> mOrigin;				///< origin offset from upper left corner in pixels
		vg::Vector2<float> mSize;				///< Sprites witdth and length in pixels.
		float mRotation;						///< Rotation of sprite in angles.
		unsigned int mLayer;					///< real layer value used by shader
		bool mUsingCamera;						///< Is the position affected by camera?
	};

}