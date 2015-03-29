
#pragma once

#include <GLES2/gl2.h>
#include <stdint.h>
#include <vector>

// TODO: Add assertions and other error handling to functions in debug mode

namespace vg
{
	namespace gl
	{
        void vertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data);

        void drawArrays(GLenum primitiveType, GLint offset, GLsizei count);

        void drawElements(GLenum primitiveType, GLsizei count, GLenum indexType, const GLvoid *indices = nullptr);

        void useProgram(GLuint programId = 0);

		void genTextures(GLuint* textureIds, GLsizei amount = 1);

		void bindTexture(GLuint textureId);

		void activeTexture(GLuint textureIndex = GL_TEXTURE0);

		void texImage2D(GLuint width, GLuint height, const std::vector<unsigned char>& pixels);

		void texParameteriMag(GLint parameter);

		void texParameteriMin(GLint parameter);
	}
}
