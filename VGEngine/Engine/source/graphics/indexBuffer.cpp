#include "..\..\include\engine\graphics\indexBuffer.h"

using namespace vg;
IndexBuffer::IndexBuffer()
	: Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
{
}

IndexBuffer::IndexBuffer(const std::vector<GLuint>& data)
	: Buffer(GL_ELEMENT_ARRAY_BUFFER, data, GL_DYNAMIC_DRAW)
{
}