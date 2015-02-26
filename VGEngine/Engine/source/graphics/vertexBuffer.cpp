
#include "engine\graphics\vertexBuffer.h"

using namespace vg;

const VertexElement VertexBuffer::gDefaultFormat[UsageCOUNT] =
{
	VertexElement{ Position, Vec2 },
	VertexElement{ Color, Vec4 },
	VertexElement{ TexCoord, Vec2 },
};

VertexBuffer::VertexBuffer()
	: Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
	, mFormat(gDefaultFormat)
	, mFormatSize(sizeof(gDefaultFormat))
{
}

VertexBuffer::VertexBuffer(const std::vector<GLfloat>& data)
	: Buffer(GL_ARRAY_BUFFER, data, GL_DYNAMIC_DRAW)
	, mFormat(gDefaultFormat)
	, mFormatSize(sizeof(gDefaultFormat))
{
}

VertexBuffer::VertexBuffer(const VertexElement* format, size_t formatSize)
	: Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
	, mFormat(format)
	, mFormatSize(formatSize)
{
}

VertexBuffer::VertexBuffer(const std::vector<float>& data, const VertexElement* format, size_t formatSize)
	: Buffer(GL_ARRAY_BUFFER, data, GL_DYNAMIC_DRAW)
	, mFormat(format)
	, mFormatSize(formatSize)
{
}

void VertexBuffer::bind()
{
	Buffer::bind();

	uint32_t stride = 0;

	for (size_t i = 0; i < mFormatSize; i++)
	{
		stride += mFormat[i].mType * sizeof(float);
	}

	uint32_t offset = 0;

	for (int i = 0; i < mFormatSize; i++)
	{
		glEnableVertexAttribArray(mFormat[i].mUsage);
		glVertexAttribPointer(mFormat[i].mUsage, mFormat[i].mType, GL_FLOAT, false, stride, (void*)(offset));
		offset += mFormat[i].mType * sizeof(float);
	}
}
