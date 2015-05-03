
#pragma once

#include "../external/glm/gtc/type_ptr.hpp"
#include <GLES2/gl2.h>
#include <string>

///@todo template value, comments

namespace vg
{
	namespace graphics
	{
		enum class UniformUsage
		{
			Projection,
			Model,
			Layer
		};

		enum class UniformType
		{
			Float,
			Vec2,
			Vec3,
			Vec4,
			Mat3,
			Mat4
		};

		/**
			Contains data for uniform variable in a shader program 
		*/
		class UniformElement
		{
		public:
			UniformElement()
				: mLocation(0u) { }

			UniformElement(UniformType type, std::string name)
				: mLocation(0u), mType(type), mName(name){ }
			
			/**
				@param location shader id for variable
			*/
			void setLocation(GLuint location)
			{
				mLocation = location;
			}

			/**
				@return 
			*/
			GLuint getLocation()
			{
				return mLocation;
			}

			/**
				@param value new value
			*/
			/*
			void setValue(T value)
			{
				mValue = value;
			}
			*/

			/**
				@return
			*/
			/*
			T getValue()
			{
				return mValue;
			}
			*/

			/**
				@return
			*/
			UniformType getType()
			{
				return mType;
			}

			/**
				@return variable name used in shader source
			*/
			std::string getName()
			{
				return mName;
			}

		private:
			GLuint mLocation;		///<
			//T mValue;				///<
			UniformType mType;		///<
			std::string mName;		///<
		};
	}
}