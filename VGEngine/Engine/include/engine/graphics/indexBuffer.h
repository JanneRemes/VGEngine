#pragma once
#include "engine/graphics/buffer.h"
#include <GLES2/gl2.h>
namespace vg
{
	namespace graphics
	{
		/**
		Buffer that contains data of indices
		*/
		class IndexBuffer :
			public Buffer<GLushort>
		{
		public:
			IndexBuffer();

			/**
			Constructor for the indexbuffer
			@param data Indice data for buffer
			*/
			IndexBuffer(const std::vector<GLushort>& data);
		};
	}
}