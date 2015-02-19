#pragma once
#include "iostream"
namespace vg
{
	/**
	Manages buffers.
	*/
	class buffer
	{
	public:
		buffer(){};
		~buffer(){};


		enum bufferType { GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER };
		enum usageType { GL_STREAM_DRAW, GL_STATIC_DRAW, GL_DYNAMIC_DRAW };

		/**
		<description>
		@param path <description>
		@return <description>
		*/
		void generateBuffers(const unsigned int amount, unsigned int* buffers);

		/**
		<description>
		@param path <description>
		@return <description>
		*/
		void deleteBuffers(const unsigned int amount, unsigned int* buffers);

		/**
		<description>
		@param path <description>
		@return <description>
		*/
		void bindBuffer(bufferType type, unsigned int buffer);

		/**
		<description>
		@param path <description>
		@return <description>
		*/
		void unbindBuffer(bufferType type);

		/**
		<description>
		@param path <description>
		@return <description>
		*/
		void setBufferData(bufferType type, unsigned int size, void* data, usageType usagetype);

	private:
	};
}