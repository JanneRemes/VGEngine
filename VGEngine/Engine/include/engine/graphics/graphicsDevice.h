
#pragma once

#include "engine/graphics/shader.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"

namespace vg
{
	class GraphicsDevice
	{
	public:
		static void draw(Shader* shader, VertexBuffer* vertices);
        static void draw(Shader* shader, VertexBuffer* vertices, IndexBuffer* indices,
            float x = 0.0f, float y = 0.0f, float rotation = 0.0f, float scale = 1.0f);
	private:
	};
}
