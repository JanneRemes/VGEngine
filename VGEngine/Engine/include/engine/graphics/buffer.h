#pragma once
#include "iostream"
namespace vg
{
	class buffer
	{
	public:
		buffer(){};
		~buffer(){};

		enum bufferType { GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER };
		enum usageType { GL_STREAM_DRAW, GL_STATIC_DRAW, GL_DYNAMIC_DRAW };

		void generateBuffers(const unsigned int amount, unsigned int* buffers);
		void deleteBuffers(const unsigned int amount, unsigned int* buffers);
		void bindBuffer(bufferType type, unsigned int buffer);
		void unbindBuffer(bufferType type);
		void setBufferData(bufferType type, unsigned int size, void* data, usageType usagetype);

	private:

	};

}