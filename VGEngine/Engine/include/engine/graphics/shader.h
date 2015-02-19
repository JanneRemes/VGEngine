
#pragma once

#include <GLES2\gl2.h>
#include <string>

/// @todo Use the dedicated logger instead
#define Log(tag, message, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, "%s, %d, %s: " message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

/// @todo Fix comments in this file

namespace vg
{
	/**
		list of supported shader types
	*/
    enum ShaderType
    {
        vertex,
		fragment
    };

	/**
        Holds shader attribute and  ids and links itself
		@todo add map of shader attribute names and ids
	*/
    class Shader
    {
    public:
		/**
			<description>
			@param type shaders type
			@param programId shader program id used for linking
			@param fileName path needed by ShaderSource asset
		*/
        Shader(ShaderType type, GLuint programId, std::string fileName);

        ~Shader();
		
		/// @todo Move function implementation to the .cpp file
		/**
			<description>
			@return shaders id used for linking
		*/
        GLuint getId();

    private:
		ShaderType mType;  ///< shaders type
		GLuint mId;        ///< shaders own id used for linking
		GLuint mProgramId; ///< shader program id used for linking
    };
}