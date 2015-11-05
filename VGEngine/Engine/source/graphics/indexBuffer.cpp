
#include "engine/graphics/indexBuffer.h"

using namespace vg::graphics;

IndexBuffer::IndexBuffer()
	: Buffer(gl::getGL_ELEMENT_ARRAY_BUFFER(), gl::getGL_DYNAMIC_DRAW())
{
}

IndexBuffer::IndexBuffer(const std::vector<unsigned short>& data)
	: Buffer(gl::getGL_ELEMENT_ARRAY_BUFFER(), data, gl::getGL_DYNAMIC_DRAW())
{
}
