
#pragma once

#include <GLES2/gl2.h>
#include <stdint.h>
#include <vector>
#include <string>
#include "../external/glm/gtc/type_ptr.hpp"

namespace vg
{
	namespace graphics
	{
		/**
			Wrappers for opengl functions. Errors are checked and printed to LogCat.
			*/
		namespace gl
		{
			void checkError();

			void vertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data);

			void drawArrays(GLenum primitiveType, GLint offset, GLsizei count);

			void drawElements(GLenum primitiveType, GLsizei count, GLenum indexType, const GLvoid *indices = nullptr);

			void useProgram(GLuint programId = 0);

			void genTextures(GLuint* textureIds, GLsizei amount = 1);

			void bindTexture(GLuint textureId);

			void activeTexture(GLuint textureIndex = GL_TEXTURE0);

			void texImage2D(GLuint width, GLuint height, const std::vector<unsigned char>& pixels, GLenum format = GL_RGBA);

			void texImage2D(GLuint width, GLuint height, const unsigned char* pixels, GLenum format = GL_RGBA);

			void texParameteri(GLenum pname, GLint parameter);

			void clear();

			void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

			void setUniform(GLuint location, glm::mat3& value);

			void setUniform(GLuint location, glm::mat4& value);

			void setUniform(GLuint location, const GLfloat* value);

			void setUniform(GLuint location, glm::vec2& value);

			void setUniform(GLuint location, glm::vec3& value);

			void setUniform(GLuint location, glm::vec4& value);

			void attachShader(GLuint program, GLuint shader);

			void linkProgram(GLuint program);

			GLint linkStatus(GLuint program);

			GLuint getUniformLocation(GLuint program, std::string name);
		}
	}
}
