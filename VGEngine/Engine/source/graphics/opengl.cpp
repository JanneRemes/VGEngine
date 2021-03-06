
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"

#if defined(OS_ANDROID)
#include <GLES2/gl2.h>
#endif
#if defined(OS_WINDOWS)
#include "../external/glew.h"
#endif

using namespace vg::graphics;
void gl::checkError()
{
	unsigned int error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Log("vgengine", "OpenGL error: %i", error, "");
	}
}

void gl::enableVertexAttribArray(unsigned int index)
{
	glEnableVertexAttribArray(index);
	checkError();
}

void gl::vertexAttribPointer(unsigned int index, int size, int stride, const void* ptr)
{
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, ptr);
	checkError();
}

void gl::drawTriangles(int count, const void *indices)
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, indices);
	checkError();
}

void gl::useProgram(unsigned int programId)
{
	glUseProgram(programId);
	checkError();
}

void gl::genTextures(unsigned int* textureIds, int amount)
{
	glGenTextures(amount, textureIds);
	checkError();
}

void gl::bindTexture(unsigned int textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	checkError();
}

void gl::activeTexture()
{
	glActiveTexture(GL_TEXTURE0);
	checkError();
}

void gl::activeTexture(unsigned int textureIndex = GL_TEXTURE0)
{
	glActiveTexture(textureIndex);
	checkError();
}

void gl::deleteTextures(const unsigned int* textures, int amount)
{
	glDeleteTextures(amount, textures);
	checkError();
}
void gl::texParameteri(unsigned int pname, int parameter)
{
	glTexParameteri(GL_TEXTURE_2D, pname, parameter);
	checkError();
}

void gl::texImage2DRGBA(unsigned int width, unsigned int height, const std::vector<unsigned char>& pixels)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	checkError();
}

void gl::texImage2DRGBA(unsigned int width, unsigned int height, const unsigned char* pixels)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	checkError();
}

void gl::texImage2DAlpha(unsigned int width, unsigned int height, const std::vector<unsigned char>& pixels)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels.data());
	checkError();
}

void gl::texImage2DAlpha(unsigned int width, unsigned int height, const unsigned char* pixels)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);
	checkError();
}

void gl::texImage2DLuminanceAlpha(unsigned int width, unsigned int height, const std::vector<unsigned char>& pixels)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, pixels.data());
	checkError();
}

void gl::texImage2DLuminanceAlpha(unsigned int width, unsigned int height, const unsigned char* pixels)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, pixels);
	checkError();
}

void gl::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	checkError();
}

void gl::clearColor(vg::Color color)
{
	glClearColor(GLclampf(color.red / 255.0f), GLclampf(color.green / 255.0f), GLclampf(color.blue / 255.0f), GLclampf(color.alpha / 255.0f));
}

void gl::setUniform(unsigned int location, glm::mat3& value)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	checkError();
}

void gl::setUniform(unsigned int location, glm::mat4& value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	checkError();
}

void gl::setUniform(unsigned int location, const float* value)
{
	glUniform1fv(location, 1, value);
	checkError();
}

void gl::setUniform(unsigned int location, glm::vec2& value)
{
	glUniform2fv(location, 1, glm::value_ptr(value));
	checkError();
}

void gl::setUniform(unsigned int location, glm::vec3& value)
{
	glUniform3fv(location, 1, glm::value_ptr(value));
	checkError();
}

void gl::setUniform(unsigned int location, glm::vec4& value)
{
	glUniform4fv(location, 1, glm::value_ptr(value));
	checkError();
}

void gl::attachShader(unsigned int program, unsigned int shader)
{
	glAttachShader(program, shader);
	checkError();
}

void gl::linkProgram(unsigned int program)
{
	glLinkProgram(program);
	checkError();
}

bool gl::linkStatus(unsigned int program)
{
	GLint result = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	checkError();
	return result == GL_TRUE;
}

unsigned int gl::getUniformLocation(unsigned int program, std::string name)
{
	unsigned int location = glGetUniformLocation(program, name.c_str());
	checkError();
	return location;
}
void gl::bindBuffer(unsigned int target, unsigned int buffer)
{
	glBindBuffer(target, buffer);
	checkError();
}
void gl::deleteBuffers(int n, const unsigned int* buffers)
{
	glDeleteBuffers(n, buffers);
	checkError();
}

void gl::bufferData(unsigned int target, signed   long  int size, const void* data, unsigned int usage)
{
	glBufferData(target, size, data, usage);
	checkError();
}
void gl::genBuffers(int n, unsigned int* buffers)
{
	glGenBuffers(n, buffers);
	checkError();
}

void gl::bufferSubData(unsigned int target, int offset, signed long int size, const void* data)
{
	glBufferSubData(target, offset, size, data);
	checkError();
}

void gl::shaderSource(unsigned int shader, int count, const char** string, const int* length)
{
	glShaderSource(shader, count, string, length);
	checkError();
}


void gl::getShaderInfoLog(unsigned int shader, int bufsize, int* length, char* infolog)
{
	glGetShaderInfoLog(shader, bufsize, length, infolog);
	checkError();
}


void gl::getShaderivInfoLog(unsigned int shader, int* params)
{
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, params);
	checkError();
}

bool gl::getShaderivCompileStatus(unsigned int shader)
{
	GLint params = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
	checkError();
	return params == GL_TRUE;
}

unsigned int gl::createProgram(void)
{
	unsigned int response = glCreateProgram();
	checkError();
	return response;
}

unsigned int gl::createVertexShader()
{
	unsigned int response = glCreateShader(GL_VERTEX_SHADER);
	checkError();
	return response;
}

unsigned int gl::createFragmentShader()
{
	unsigned int response = glCreateShader(GL_FRAGMENT_SHADER);
	checkError();
	return response;
}

void gl::bindAttribLocation(unsigned int program, unsigned int index, const char* name)
{
	glBindAttribLocation(program, index, name);
	checkError();
}

void gl::compileShader(unsigned int shader)
{
	glCompileShader(shader);
	checkError();
}


// texture
unsigned int gl::getGL_LINEAR()
{
	return GL_LINEAR;
}

unsigned int gl::getGL_NEAREST()
{
	return GL_NEAREST;
}

unsigned int gl::getGL_REPEAT()
{
	return GL_REPEAT;
}

unsigned int gl::getGL_CLAMP_TO_EDGE()
{
	return GL_CLAMP_TO_EDGE;
}

unsigned int gl::getGL_TEXTURE_MAG_FILTER()
{
	return GL_TEXTURE_MAG_FILTER;
}

unsigned int gl::getGL_TEXTURE_MIN_FILTER()
{
	return GL_TEXTURE_MIN_FILTER;
}

unsigned int gl::getGL_TEXTURE_WRAP_S()
{
	return GL_TEXTURE_WRAP_S;
}

unsigned int gl::getGL_TEXTURE_WRAP_T()
{
	return GL_TEXTURE_WRAP_T;
}


// buffers
unsigned int gl::getGL_ARRAY_BUFFER()
{
	return GL_ARRAY_BUFFER;
}

unsigned int gl::getGL_ELEMENT_ARRAY_BUFFER()
{
	return GL_ELEMENT_ARRAY_BUFFER;
}

unsigned int gl::getGL_DYNAMIC_DRAW()
{
	return GL_DYNAMIC_DRAW;
}

unsigned int gl::getGL_STATIC_DRAW()
{
	return GL_STATIC_DRAW;
}
