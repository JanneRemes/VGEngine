#pragma once
#include "engine\graphics\buffer.h"
#include <GLES2/gl2.h>
namespace vg
{
	class IndexBuffer :
		public Buffer<GLuint>
	{
	public:
		IndexBuffer();
		IndexBuffer(const std::vector<GLuint>& data);
	};

}