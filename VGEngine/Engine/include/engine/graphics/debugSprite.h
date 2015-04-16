
#pragma once

#include "engine/graphics/texture.h"
#include "engine/graphics/shader.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"

#include <vector>
#include <string>

namespace vg
{
	/**
		unbatched test sprite
	*/
    class DebugSprite
    {
    public:
		/**
			@param textureFileName path to texture
		*/
        DebugSprite(const std::string& textureFileName, float x, float y, float rotation);

		/**
			<description>
		*/
        ~DebugSprite();

		/**
			creates new index and vertex buffers
		*/
		void initialize();

		/**
			draws the sprite
		*/
        void draw(Shader& shader);
		
		/**
			<description>
			@return pointer to current texture
		*/
        Texture* getTexture();

        void setPosition(float x, float y);

        void move(float x, float y);

        void setRotation(float rotation);

        void rotate(float rotatation);

        //void setScale(float scale);
        //void scale(float scale);

        std::vector<float> defaultVertices =
        {
            // Position Vec2
            // Color Vec4
            // TexCoord Vec2

            //left up
            -1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f,
            0.0f, 1.0f,

            //left down
            -1.0f, -1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f,

            //right down
            1.0f, -1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f,

            //right up
            1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f
        };

        std::vector<uint> defaultIndices = 
        {
            0u, 1u, 2u,
            0u, 2u, 3u
        };

    private:
        void updateVertices();

        Texture* mTexture;				///<description>			
        //VertexBuffer* mVertexBuffer;	///<description>
        //IndexBuffer* mIndexBuffer;		///<description>
        glm::vec2 mPosition;
        float mRotation;
        //float mScale;
        std::vector<float> mVertices;
        std::vector<uint> mIndices;
    };
}