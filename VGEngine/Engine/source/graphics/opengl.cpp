
#include "engine/graphics/opengl.h"

void vg::gl::VertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, data);
}

void vg::gl::DrawArrays(GLenum primitiveType, GLint offset, GLsizei count)
{
    glDrawArrays(primitiveType, offset, count);
}

void vg::gl::DrawElements(GLenum primitiveType, GLsizei count, GLenum indexType, GLvoid *indices)
{
    glDrawElements(primitiveType, count, indexType, indices);
}

void vg::gl::UseProgram(GLuint programId)
{
    glUseProgram(programId);
}