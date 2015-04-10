
#include "engine/graphics/graphicsDevice.h"
#include "engine/graphics/opengl.h"

using namespace vg;

void GraphicsDevice::draw(Shader* shader, VertexBuffer* vertices)
{
	gl::useProgram(shader->getProgramId());

	vertices->bind();
	
	gl::drawArrays(GL_TRIANGLES, 0, vertices->getSize());

	vertices->unbind();

	gl::useProgram();
}

void GraphicsDevice::draw(Shader* shader, VertexBuffer* vertices, IndexBuffer* indices,
    float x, float y, float rotation, float scale)
{
    gl::useProgram(shader->getProgramId());

    vertices->bind();
    indices->bind();

    shader->setPosition(x, y);
    shader->setRotation(rotation);
    shader->setScale(scale);
    shader->updateUniforms();

    gl::drawElements(GL_TRIANGLES, vertices->getSize(), GL_UNSIGNED_INT);

    shader->resetUniforms();

    indices->unbind();
    vertices->unbind();

    gl::useProgram();
}


