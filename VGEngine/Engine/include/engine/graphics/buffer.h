
#pragma once

#include <vector>
#include <GLES2/gl2.h>

namespace vg
{
	/**
		Manages and creates buffers
	*/
	template<class T>
	class Buffer
	{
	public:

		/**
		<description>
		@param target
		@param usage
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
		<description>
		@param target
		@param data
		@param usage
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
		<description>
		*/
		virtual ~Buffer()
		{
			glDeleteBuffers(1, &mId);
		}

		/**
		<description>
		@param data
		*/
		void setData(const std::vector<T>& data)
		{
			glBindBuffer(mTarget, mId);
			glBufferData(mTarget, data.size() * sizeof(T), &data[0], mUsage);
			glBindBuffer(mTarget, 0);
			mSize = data.size();
		}

		/**
		<description>
		@param offset
		@param data
		*/
		void setData(size_t offset, const std::vector<T>& data)
		{
			glBindBuffer(mTarget, mId);
			glBufferSubData(mTarget, offset * sizeof(T), data.size() * sizeof(T), &data[0]);
			glBindBuffer(mTarget, 0);
		}

		/**
		<description>
		*/
		virtual void bind()
		{
			glBindBuffer(mTarget, mId);
		}

		/**
		<description>
		*/
		void unbind()
		{
			glBindBuffer(mTarget, 0);
		}

		/**
		<description>
		*/
		size_t getSize() const
		{
			return mSize;
		}

		/**
		<description>
		*/
		GLuint getId() const
		{
			return mId;
		}
	protected:
		size_t mSize = 0;		///< <description>
		GLuint mId = 0;			///< <description>
		const GLenum mTarget;	///< <description>
		const GLenum mUsage;	///< <description>
	};
}
