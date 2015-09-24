
#pragma once

#include "engine/game/component.h"
#include "engine/utility/Vector2.h"

namespace vg
{

	/**
	Component for managing gameObject by rotating or scaling
	*/
	class TransformComponent :
		public Component
	{
	public:

		TransformComponent();
		TransformComponent(const TransformComponent &transform);
        /**
        @param textureFileName path to texture
        @param position position of upper left corner in pixels
        @param size width and lenght of the sprite in pixels
        @param rotation angle of rotation clockwise
        @param layer higher layers are drawn over lower ones
        @param origin offset of origin in pixels from upper left corner
        */
        TransformComponent(vg::Vector2<int> position, vg::Vector2<int> size,
            float rotation, uint layer = getDefaultLayer(), vg::Vector2<int> origin = vg::Vector2<int>(0, 0));
		
        ~TransformComponent();

        /**
        @return local position (only taking into account this component큦 position not parent큦 position)
        */
        vg::Vector2<int> getLocalPosition();

		/**
		@return world position (adds parent gameobject큦 position to this components local position)
		*/
		vg::Vector2<int> getWorldPosition();
        /**
        Set position value to be used on draw calls.
        */
        void setPosition(const vg::Vector2<int> position);

        /**
        Add to the position value to be used on draw calls.
        */
        void move(vg::Vector2<int> change);

        /**
		@return local size (only taking into account this component큦 size not parent큦 size)
        */
        vg::Vector2<int> getLocalSize();

		/**
		@return world size (adds parent gameobject큦 size to this components local size)
		*/
		vg::Vector2<int> getWorldSize();

        /**
        Set position value to be used on draw calls.
        */
        void setSize(const vg::Vector2<int> size);

        /**
		@return local rotattion (only taking into account this component큦 rotation not parent큦 rotation)
        */
        float getLocalRotation();

		/**
		@return world rotation (adds parent gameobject큦 rotation to this components local rotation)
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
        @return layer value clamped to range of 0-1.
        */
        float getLayer();

        /**
        @param layer value ranging from 0 to 10000.
        */
        void setLayer(uint layer);

        /**
        <description>
        */
        vg::Vector2<int> getOrigin();

        /**
        Set origin offset.
        */
        void setOrigin(const vg::Vector2<int> origin);

	private:
		static uint mCurrentLayer;
		static uint getDefaultLayer();
        vg::Vector2<int> mPosition;     ///< Position of top left corner in pixels.
        vg::Vector2<int> mOrigin;		///< origin offset from upper left corner in pixels
        vg::Vector2<int> mSize;			///< Sprites witdth and length in pixels.
        float mRotation;                ///< Rotation of sprite in angles.
        uint mLayer;                   ///< Layer where the sprite will be drawn.
	};

}