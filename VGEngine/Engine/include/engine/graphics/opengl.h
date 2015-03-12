
#include <GLES2/gl2.h>
#include <stdint.h>

// TODO: Add assertions and other error handling to functions in debug mode

namespace vg
{
	namespace gl
	{
		void VertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data)
		{
			glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, data);
		}

		void DrawArrays(GLenum primitiveType, GLint offset, GLsizei count)
		{
			glDrawArrays(primitiveType, offset, count);
		}

		void DrawElements(GLenum primitiveType, GLsizei count, GLenum indexType, GLvoid *indices = nullptr)
		{
			glDrawElements(primitiveType, count, indexType, indices);
		}

		void UseProgram(GLuint programId = 0)
		{
			glUseProgram(programId);
		}
	}
}
