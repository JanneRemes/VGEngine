
#pragma once

#include <stdint.h>

namespace vg
{
	/**
	<description>
	@param fileManager <description>
	@return <description>
	*/
	enum VertexElementUsage
	{
		Position,
		Color,
		TexCoord,

		UsageCOUNT
	};

	/**
	<description>
	@param fileManager <description>
	@return <description>
	*/
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

	/**
	<description>
	@param fileManager <description>
	@return <description>
	*/
	struct VertexElement
	{
		uint32_t mUsage;
		uint32_t mType;
	};
}
