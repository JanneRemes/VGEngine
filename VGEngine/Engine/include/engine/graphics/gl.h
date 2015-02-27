
#include <GLES2\gl2.h>
#include <stdint.h>

namespace vg
{
	namespace gl
	{
		void VertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data)
		{
			glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, data);
		}
	}
}
