
#pragma once

#include "engine/graphics/texture.h"
#include "engine/graphics/shader.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/utility/Vector2.h"

#include <vector>
#include <string>

namespace vg
{
	namespace graphics
	{
		/**
			Unbatched test sprite.
			*/
		class DebugSprite
		{
		public:
			/**
				@param textureFileName path to texture
				@param position position of upper left corner in pixels
				@param size width and lenght of the sprite in pixels
				@param rotation angle of rotation clockwise
				@param layer higher layers are drawn over lower ones
				@param origin offset of origin in pixels from upper left corner
				*/
			DebugSprite(const std::string& texturePath, vg::Vector2<int> position,
				vg::Vector2<int> size, float rotation, uint layer, vg::Vector2<int> origin = vg::Vector2<int>(0, 0));

			/**
				Deletes the dynamic buffers.
				*/
			~DebugSprite();

			/**
				draws the sprite
				*/
			void draw(Shader* shader);

			/**
				<description>
				@return pointer to current texture
				*/
			Texture* getTexture();

			/**
				Set position value to be used on draw calls.
				*/
			void setPosition(const vg::Vector2<int> position);

			/**
				Add to the position value to be used on draw calls.
				*/
			void move(vg::Vector2<int> change);

			/**
				Set rotation value to be used on draw calls.
				*/
			void setRotation(float rotation);

			/**
				Add to the rotation value to be used on draw calls.
				*/
			void rotate(float rotatation);

			/**
				Set origin offset.
				*/
			void setOrigin(const vg::Vector2<int> origin);


			/**
				Default vertice values without transformation.
				*/
			std::vector<float> defaultVertices =
			{
				// Position Vec2
				// Color Vec4
				// TexCoord Vec2

				//left up
				0.0f, 0.0f,
				0.5f, 0.5f, 0.5f, 1.0f,
				0.0f, 1.0f,

				//left down
				0.0f, 1.0f,
				1.0f, 0.0f, 0.0f, 1.0f,
				0.0f, 0.0f,

				//right down
				1.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				1.0f, 0.0f,

				//right up
				1.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 1.0f,
				1.0f, 1.0f
			};

			/**
				Default indices for two triangles forming a quad.
				*/
			std::vector<uint> defaultIndices =
			{
				0u, 1u, 2u,
				0u, 2u, 3u
			};

		private:
			void updateVertices();

			Texture* mTexture;				///< Texture for drawing	
			//VertexBuffer* mVertexBuffer;	///< VertexBuffer that will be binded before drawing.
			//IndexBuffer* mIndexBuffer;		///< IndexBuffer that will be binded before drawing.
			vg::Vector2<int> mPosition;     ///< Position of top left corner in pixels.
			vg::Vector2<int> mOrigin;		///< origin offset from upper left corner in pixels
			vg::Vector2<int> mSize;			///< Sprites witdth and length in pixels.
			float mRotation;                ///< Rotation of sprite in angles.
			uint mLayer;                    ///< Layer where the sprite will be drawn.
			std::vector<float> mVertices;   ///< Vertices that will be binded to buffer.
			std::vector<uint> mIndices;     ///< Indices that will be binded to buffer.
		};
	}
}