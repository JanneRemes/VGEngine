#pragma once
#include "engine/graphics/buffer.h"
#include <GLES2/gl2.h>
namespace vg
{

	/**
	Buffer that contains data of indices
	*/
	class IndexBuffer :
		public Buffer<GLuint>
	{
	public:
		IndexBuffer();

		/**
		Constructor for the indexbuffer
		@param data Indice data for buffer
		*/
		IndexBuffer(const std::vector<GLuint>& data);
	};

}