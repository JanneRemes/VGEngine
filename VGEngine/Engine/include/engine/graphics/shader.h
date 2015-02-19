
#pragma once

#include <GLES2\gl2.h>
#include <string>

/// @todo Use the dedicated logger instead
#define Log(tag, message, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, "%s, %d, %s: " message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

/// @todo Fix comments in this file

namespace vg
{
	/**
		class_description
	*/
    enum ShaderType
    {
        vertex,
		fragment
    };

	/**
		<description>
	*/
    class Shader
    {
    public:
		/**
			<description>
			@param type <description>
			@param programId <description>
			@param fileName <description>
		*/
        Shader(ShaderType type, GLuint programId, std::string fileName);

        ~Shader();
		
		/// @todo Move function implementation to the .cpp file
		/**
			<description>
			@return shaders id used for linking
		*/
        GLuint getId(){ return mId; };

    private:
		ShaderType mType;  ///< description
		GLuint mId;        ///< description
		GLuint mProgramId; ///< description
    };
}