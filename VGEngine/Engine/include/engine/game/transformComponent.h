
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
		// friends
		friend class RenderSystem;
		friend class Scene;

	public:
		/**
		Layers for rendering. Sprites on higher layers are drawn on top of lower ones.
		BOTTOM	recommended for backgrounds
		MIDDLE	default value
		TOP		recommended for user interface
		*/
		enum LayerGroup
		{
			BOTTOM = 0, // 1 - 999
			LOW,		// 1 000 - 1 999
			MIDDLE,		// 2 000 - 7 999
			HIGH,		// 8 000 - 8 999
			TOP			// 9 000 - 10 000
		};

		/**
		Default constructor
		*/
		TransformComponent();

		/**
		Copy constructor
		*/
		TransformComponent(const TransformComponent &transform);

		/**
		Size and origin are set to (0, 0)
		@param position of upper left corner
		@param layerGroup higher layers are drawn over lower ones
		@param useCamera true if the position is affected by camera
		*/
		TransformComponent(Vec2f position, LayerGroup layerGroup = MIDDLE, bool useCamera = true);
		
		/**
		@param position position of upper left corner
		@param size width and lenght of the sprite
		@param rotation angle of rotation clockwise
		@param origin offset of origin from upper left corner
		@param layerGroup higher layers are drawn over lower ones
		@param useCamera true if the position is affected by camera
		*/
		TransformComponent(vg::Vec2f position, vg::Vec2f size, float rotation = 0.0f, 
			vg::Vec2f origin = vg::Vec2f(), LayerGroup layerGroup = MIDDLE, bool useCamera = true);

		/**
		@param leftTop corner of rectangle
		@param rightBottom corner of rectangle
		@param origin offset of origin from upper left corner
		@param layerGroup higher layers are drawn over lower ones
		@param useCamera true if the position is affected by camera
		*/
		TransformComponent(Vec2f leftTop, Vec2f rightBottom, Vec2f origin, LayerGroup layerGroup = MIDDLE, bool useCamera = true);

		~TransformComponent();

		/**
		@return local position (only taking into account this component´s position not parent´s position)
		*/
		Vec2f getLocalPosition();

		/**
		@return world position (adds parent gameobject´s position to this components local position)
		*/
		Vec2f getWorldPosition();
		
		/**
		Set position value to be used on draw calls.
		*/
		void setPosition(const Vec2f position);

		/**
		@param change Value that will be added to position
		*/
		void move(Vec2f change);

		/**
		@return size in pixels
		*/
		Vec2f getSize();

		/**
		Set position value to be used on draw calls.
		*/
		void setSize(const Vec2f size);

		/**
		@param x value
		*/
		void setX(float x);

		/**
		@param y value
		*/
		void setY(float y);

		/**
		@return rotation in degrees
		*/
		float getLocalRotation();

		/**
		@return rotation taking possible parent's rotation into account
		*/
		float getWorldRotation();

		/**
		Same as getWorldRotation()
		@return rotation taking possible parent's rotation into account
		*/
		float getRotation();

		/**
		Set rotation value to be used on draw calls.
		*/
		void setRotation(float rotation);

		/**
		Add to the rotation value
		*/
		void rotate(float rotatation);

		/**
		@param layerGroup layer where GameObject will be drawn
		*/
		void setLayer(LayerGroup layerGroup);
		
		/**
		@return current LayerGroup 
		*/
		LayerGroup getLayerGroup();

		/**
		@return origin offset
		*/
		Vec2f getOrigin();

		/**
		Set origin offset.
		*/
		void setOrigin(const Vec2f origin);

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
		bool contains(Vec2f point);

	private:
		//functions that aren't visible to end user
		static float getMaxLayer();
		float getLayer();

		Vec2f mPosition;	///< Position of top left corner
		Vec2f mOrigin;		///< origin offset from upper left corner
		Vec2f mSize;		///< Sprites witdth and length
		float mRotation;				///< Rotation of sprite in angles.
		LayerGroup mLayerGroup;			///< LayerGroup where GameObject will be drawn
		unsigned int mLayer;			///< real layer value used by shader
		bool mUsingCamera;				///< Is the position affected by camera?
	};

}