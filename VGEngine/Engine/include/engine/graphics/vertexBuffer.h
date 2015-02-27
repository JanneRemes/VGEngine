
#pragma once

#include "engine\graphics\buffer.h"
#include <GLES2/gl2.h>
#include <vector>

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

	class VertexBuffer :
		public Buffer<float>
	{
	public:
		/**
		Default constructor that uses default type format
		*/
		VertexBuffer();
		/**
		Constructor that uses default format
		@param raw data in vector that you want to draw
		*/
		VertexBuffer(const std::vector<float>& data);
		/**
		Constructor used if user wants custom type format
		@param raw float data in vector
		@param custom type format
		*/
		VertexBuffer(const std::vector<float>& data, const std::vector<VertexElement>& format);
		/**
		Constructor that takes in 
		@param custom type format
		*/
		VertexBuffer(const std::vector<VertexElement>& format);
		/**
		Binds raw vertex data into buffer using format and stride
		*/
		void bind() override;
	private:
		const uint32_t mStride;///< Stride used in bind. Calculated in constructor from format
		//const size_t mFormatSize;///< Size of current formats
		const std::vector<VertexElement> mFormat;///< vector that has format currently in use

		static const std::vector<VertexElement>& gDefaultFormat;///< default vertexElement format
	};

}
