
#pragma once

#include <vector>
#include <GLES2/gl2.h>

namespace vg
{
	/**
		wtb description
	*/
	template<class T>
	class Buffer
	{
	public:
		Buffer(GLenum target, GLenum usage)
			: mTarget(target)
			, mUsage(usage)
		{
			glGenBuffers(1, &mId);
			glBindBuffer(mTarget, mId);
			glBufferData(mTarget, 0, nullptr, mUsage);
			glBindBuffer(mTarget, 0);
		}

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

		virtual ~Buffer()
		{
			glDeleteBuffers(1, &mId);
		}

		void setData(const std::vector<T>& data)
		{
			glBindBuffer(mTarget, mId);
			glBufferData(mTarget, data.size() * sizeof(T), &data[0], mUsage);
			glBindBuffer(mTarget, 0);
			mSize = data.size();
		}

		void setData(size_t offset, const std::vector<T>& data)
		{
			glBindBuffer(mTarget, mId);
			glBufferSubData(mTarget, offset * sizeof(T), data.size() * sizeof(T), &data[0]);
			glBindBuffer(mTarget, 0);
		}

		virtual void bind()
		{
			glBindBuffer(mTarget, mId);
		}

		void unbind()
		{
			glBindBuffer(mTarget, 0);
		}

		size_t getSize() const
		{
			return mSize;
		}

		GLuint getId() const
		{
			return mId;
		}
	protected:
		size_t mSize = 0;
		GLuint mId = 0;
		const GLenum mTarget;
		const GLenum mUsage;
	};
}
