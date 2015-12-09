
#pragma once

#include <vector>
#include "engine\graphics\opengl.h"

namespace vg
{
	namespace graphics
	{
		/**
		Manages and contains buffer data
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
			Buffer(unsigned int target, unsigned int usage)
				: mTarget(target)
				, mUsage(usage)
			{
				gl::genBuffers(1, &mId);
				gl::bindBuffer(mTarget, mId);
				gl::bufferData(mTarget, 0, nullptr, mUsage);
				gl::bindBuffer(mTarget, 0);
			}

			/**
			Constructs a buffer with data
			@param target Specifies the target to which the buffer object is bound
			@param data Specifies a pointer to data that will be copied into the data store for initialization
			@param usage Specifies the expected usage pattern of the data store
			*/
			Buffer(unsigned int target, const std::vector<T>& data, unsigned int usage)
				: mTarget(target)
				, mUsage(usage)
			{
				gl::genBuffers(1, &mId);
				gl::bindBuffer(mTarget, mId);
				gl::bufferData(mTarget, data.size() * sizeof(T), &data[0], mUsage);
				gl::bindBuffer(mTarget, 0);
				mSize = data.size();
			}

			/**
			Destructor for the buffer
			*/
			virtual ~Buffer()
			{
				gl::deleteBuffers(1, &mId);
			}

			/**
			Creates and initializes a buffer object's data store
			@param data Specifies a pointer to data that will be copied into the data store for initialization
			*/
			void setData(const std::vector<T> *data)
			{
				gl::bindBuffer(mTarget, mId);
				gl::bufferData(mTarget, data->size() * sizeof(T), &data->at(0), mUsage);
				gl::bindBuffer(mTarget, 0);
				mSize = data->size();
			}

			/**
			Updates a subset of a buffer object's data store
			@param offset Specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes
			@param data Specifies a pointer to the new data that will be copied into the data store
			*/
			void setData(size_t offset, const std::vector<T> *data)
			{
				gl::bindBuffer(mTarget, mId);
				gl::bufferSubData(mTarget, offset * sizeof(T), data.size() * sizeof(T), &data->at(0));
				gl::bindBuffer(mTarget, 0);
			}

			/**
			Bind a buffer object
			*/
			virtual void bind()
			{
				gl::bindBuffer(mTarget, mId);
			}

			/**
			Unbind a buffer object
			*/
			void unbind()
			{
				gl::bindBuffer(mTarget, 0);
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
			unsigned int getId() const
			{
				return mId;
			}

		protected:
			size_t mSize = 0;				///< Size of the pointer to data that will be copied into the data store for initialization
			unsigned int mId = 0;			///< An array in which the generated buffer object names are stored
			const unsigned int mTarget;		///< Target to which the buffer object is bound
			const unsigned int mUsage;		///< Usage pattern of the data store
		};
	}
}
