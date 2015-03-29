
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
        DebugSprite(const std::string& textureFileName);

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

    private:
        Texture* mTexture;				///<description>			
        VertexBuffer* mVertexBuffer;	///<description>
        IndexBuffer* mIndexBuffer;		///<description>
    };
}