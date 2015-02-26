
#pragma once

#include "engine\graphics\buffer.h"
#include <GLES2/gl2.h>
#include <vector>

namespace vg
{
	enum VertexElementUsage
	{
		Position,
		Color,
		TexCoord,

		UsageCOUNT
	};

	enum VertexElementType
	{
		Float = 1,
		Vec2 = 2,
		Vec3 = 3,
		Vec4 = 4,
		Mat2 = 2 * 2,
		Mat3 = 3 * 3,
		Mat4 = 4 * 4,

		TypeCOUNT
	};

	struct VertexElement
	{
		uint32_t mUsage;
		uint32_t mType;
	};

	class VertexBuffer :
		public Buffer<float>
	{
	public:
		VertexBuffer();
		VertexBuffer(const std::vector<float>& data);
		VertexBuffer(const std::vector<float>& data, const VertexElement* format, size_t formatSize);
		VertexBuffer(const VertexElement* format, size_t formatSize);

		void bind() override;
	private:
		const size_t mFormatSize;
		const VertexElement* mFormat;
		static const VertexElement gDefaultFormat[];
	};

}
