
#include "engine/graphics/graphicsDevice.h"
#include "engine/graphics/opengl.h"

using namespace vg::graphics;

void GraphicsDevice::draw(Shader* shader, VertexBuffer* vertices)
{
	gl::useProgram(shader->getProgramId());

	vertices->bind();
	
	gl::drawArrays(GL_TRIANGLES, 0, vertices->getSize());

	vertices->unbind();

	gl::useProgram();
}

void GraphicsDevice::draw(Shader* shader, VertexBuffer* vertices, IndexBuffer* indices)
{
    vertices->bind();
    indices->bind();

    gl::drawElements(GL_TRIANGLES, vertices->getSize(), GL_UNSIGNED_INT);

    indices->unbind();
    vertices->unbind();
}


