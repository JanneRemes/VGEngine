
#include "engine/graphics/opengl.h"

void vg::gl::vertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, data);
}

void vg::gl::drawArrays(GLenum primitiveType, GLint offset, GLsizei count)
{
    glDrawArrays(primitiveType, offset, count);
}

void vg::gl::drawElements(GLenum primitiveType, GLsizei count, GLenum indexType, const GLvoid *indices)
{
    glDrawElements(primitiveType, count, indexType, indices);
}

void vg::gl::useProgram(GLuint programId)
{
    glUseProgram(programId);
}

void vg::gl::genTextures(GLuint* textureIds, GLsizei amount)
{
	glGenTextures(amount, textureIds);
}

void vg::gl::bindTexture(GLuint textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void vg::gl::activeTexture(GLuint textureIndex)
{
	glActiveTexture(textureIndex);
}

void vg::gl::texParameteriMag(GLint parameter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, parameter);
}

void vg::gl::texParameteriMin(GLint parameter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, parameter);
}

void vg::gl::texImage2D(GLuint width, GLuint height, const std::vector<unsigned char>& pixels)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
}
