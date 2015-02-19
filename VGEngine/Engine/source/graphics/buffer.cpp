#include "buffer.h"
#include <GLES/gl.h>
using namespace vg;

void buffer::generateBuffers(const unsigned int amount, unsigned int* buffers)
{
	glGenBuffers(amount, buffers);
}

void buffer::deleteBuffers(const unsigned int amount, unsigned int* buffers)
{
	glDeleteBuffers(amount, buffers);
}

void buffer::bindBuffer(bufferType type, unsigned int buffer)
{
	glBindBuffer(type, buffer);
}

void buffer::unbindBuffer(bufferType type)
{
	glBindBuffer(type, 0u);
}

void buffer::setBufferData(bufferType type, unsigned int size, void* data, usageType usagetype)
{
	glBufferData(type, size, data, usagetype);
}