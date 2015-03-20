
#include "engine/graphics/graphicsDevice.h"
#include "engine/graphics/opengl.h"

using namespace vg;

void GraphicsDevice::draw(Shader& shader, VertexBuffer& vertices)
{
	gl::UseProgram(shader.getProgramId());

	vertices.bind();
	
	gl::DrawArrays(GL_TRIANGLES, 0, vertices.getSize());

	vertices.unbind();

	gl::UseProgram();
}

void GraphicsDevice::draw(Shader& shader, VertexBuffer& vertices, IndexBuffer& indices)
{
	gl::UseProgram(shader.getProgramId());

	vertices.bind();
	indices.bind();

	gl::DrawElements(GL_TRIANGLES, vertices.getSize(), GL_UNSIGNED_INT);

	indices.unbind();
	vertices.unbind();
	
	gl::UseProgram();
}
