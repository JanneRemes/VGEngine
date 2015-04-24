
#pragma once

#include <vector>
#include <GLES2/gl2.h>

namespace vg
{
	/**
		Manages buffers
	*/
	template<class T>
	class Buffer
	{
	public:

		/**
		Constructs a buffer
		@param target Specifies the target to which the buffer object is bound
		@param usage Specifies the expected usage pattern of the data store
		*/
		Buffer(GLenum target, GLenum usage)
			: mTarget(target)
			, mUsage(usage)
		{
			glGenBuffers(1, &mId);
			glBindBuffer(mTarget, mId);
			glBufferData(mTarget, 0, nullptr, mUsage);
			glBindBuffer(mTarget, 0);
		}

		/**
		Constructs a buffer with data
		@param target Specifies the target to which the buffer object is bound
		@param data Specifies a pointer to data that will be copied into the data store for initialization
		@param usage Specifies the expected usage pattern of the data store
		*/
		Buffer(GLenum target, const std::vector<T>& data, GLenum usage)
			: mTarget(target)
			, mUsage(usage)
		{
			glGenBuffers(1, &mId);
			glBindBuffer(mTarget, mId);
			glBufferData(mTarget, data.size() * sizeof(T), &data[0], mUsage);
			glBindBuffer(mTarget, 0);
			mSize = data.size();
		}

		/**
		Destructor for the buffer
		*/
		virtual ~Buffer()
		{
			glDeleteBuffers(1, &mId);
		}

		/**
		Creates and initializes a buffer object's data store
		@param data Specifies a pointer to data that will be copied into the data store for initialization
		*/
		void setData(const std::vector<T>& data)
		{
			glBindBuffer(mTarget, mId);
			glBufferData(mTarget, data.size() * sizeof(T), &data[0], mUsage);
			glBindBuffer(mTarget, 0);
			mSize = data.size();
		}

		/**
		Updates a subset of a buffer object's data store
		@param offset Specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes
		@param data Specifies a pointer to the new data that will be copied into the data store
		*/
		void setData(size_t offset, const std::vector<T>& data)
		{
			glBindBuffer(mTarget, mId);
			glBufferSubData(mTarget, offset * sizeof(T), data.size() * sizeof(T), &data[0]);
			glBindBuffer(mTarget, 0);
		}

		/**
		Bind a buffer object
		*/
		virtual void bind()
		{
			glBindBuffer(mTarget, mId);
		}

		/**
		Unbind a buffer object
		*/
		void unbind()
		{
			glBindBuffer(mTarget, 0);
		}

		/**
		@return Returns the size of the data inside the buffer
		*/
		size_t getSize() const
		{
			return mSize;
		}

		/**
		Returns the buffer id
		*/
		GLuint getId() const
		{
			return mId;
		}
	protected:
		size_t mSize = 0;		///< Size of the pointer to data that will be copied into the data store for initialization
		GLuint mId = 0;			///< An array in which the generated buffer object names are stored
		const GLenum mTarget;	///< Target to which the buffer object is bound
		const GLenum mUsage;	///< Usage pattern of the data store
	};
}
