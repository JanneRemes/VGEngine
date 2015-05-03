
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"

using namespace vg::graphics;

void gl::checkError()
{
	GLuint error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Log("ERROR", "OpenGL error: %i", error, "");
	}
}

void gl::vertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, data);
	checkError();
}

void gl::drawArrays(GLenum primitiveType, GLint offset, GLsizei count)
{
    glDrawArrays(primitiveType, offset, count);
	checkError();
}

void gl::drawElements(GLenum primitiveType, GLsizei count, GLenum indexType, const GLvoid *indices)
{
    glDrawElements(primitiveType, count, indexType, indices);
	checkError();
}

void gl::useProgram(GLuint programId)
{
    glUseProgram(programId);
	checkError();
}

void gl::genTextures(GLuint* textureIds, GLsizei amount)
{
	glGenTextures(amount, textureIds);
	checkError();
}

void gl::bindTexture(GLuint textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	checkError();
}

void gl::activeTexture(GLuint textureIndex)
{
	glActiveTexture(textureIndex);
	checkError();
}

void gl::texParameteri(GLenum pname, GLint parameter)
{
	glTexParameteri(GL_TEXTURE_2D, pname, parameter);
	checkError();
}

void gl::texImage2D(GLuint width, GLuint height, const std::vector<unsigned char>& pixels, GLenum format)
{
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels.data());
	checkError();
}

void gl::texImage2D(GLuint width, GLuint height, const unsigned char* pixels, GLenum format)
{
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	checkError();
}

void gl::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	checkError();
}

void gl::clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	glClearColor(red, green, blue, alpha);
	checkError();
}

void gl::setUniform(GLuint location, glm::mat4& value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	checkError();
}

void gl::setUniform(GLuint location, float& value)
{
	glUniform1f(location, value);
	checkError();
}
