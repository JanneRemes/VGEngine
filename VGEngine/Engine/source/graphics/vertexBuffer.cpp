
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/opengl.h"

using namespace vg::graphics;

const std::vector<VertexElement>& VertexBuffer::gDefaultFormat 
{
	{ Position, Vec2 },
	{ Color, Vec4 },
	{ TexCoord, Vec2 }
};

static uint32_t countStride(const std::vector<VertexElement>& format)
{
	uint32_t stride = 0;

	for (int i = 0; i < format.size(); i++)
	{
		stride += format[i].mType;
	}
    return stride;
}

VertexBuffer::VertexBuffer()
	: VertexBuffer(gDefaultFormat)
{
}

VertexBuffer::VertexBuffer(const std::vector<VertexElement>& format)
	: Buffer(gl::getGL_ARRAY_BUFFER(), gl::getGL_DYNAMIC_DRAW())
	, mFormat(format)
	, mStride(countStride(format))
{
}

VertexBuffer::VertexBuffer(const std::vector<float>& data)
	: VertexBuffer(data, gDefaultFormat)
{
}

VertexBuffer::VertexBuffer(const std::vector<float>& data, const std::vector<VertexElement>& format)
	: Buffer(gl::getGL_ARRAY_BUFFER(), data, gl::getGL_DYNAMIC_DRAW())
	, mFormat(format)
	, mStride(countStride(format))
{
}

void VertexBuffer::bind()
{
	Buffer::bind();
	uint32_t offset = 0;

	for (int i = 0; i < mFormat.size(); i++)
	{
		gl::enableVertexAttribArray(mFormat[i].mUsage);
		gl::vertexAttribPointer(mFormat[i].mUsage, mFormat[i].mType, mStride * sizeof(float), (void*)(offset));
		offset += mFormat[i].mType * sizeof(float);
	}
}
