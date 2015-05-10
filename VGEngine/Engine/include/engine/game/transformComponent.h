
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
        <description>
        */
        vg::Vector2<int> getPosition();

        /**
        Set position value to be used on draw calls.
        */
        void setPosition(const vg::Vector2<int> position);

        /**
        Add to the position value to be used on draw calls.
        */
        void move(vg::Vector2<int> change);

        /**
        <description>
        */
        vg::Vector2<int> getSize();

        /**
        Set position value to be used on draw calls.
        */
        void setSize(const vg::Vector2<int> size);

        /**
        <description>
        */
        float getRotation();

        /**
        Set rotation value to be used on draw calls.
        */
        void setRotation(float rotation);

        /**
        Add to the rotation value to be used on draw calls.
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