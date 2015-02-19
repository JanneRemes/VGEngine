#pragma once
#include <GLES2\gl2.h>
#include <string>
#define Log(tag, message, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, "%s, %d, %s: " message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

namespace vg
{
    enum ShaderType
    {
        vertex, fragment
    };

    class Shader
    {
    public:
        Shader(ShaderType type, GLuint programId, std::string fileName);
        ~Shader();

        /// @return shaders id used for linking
        GLuint getId(){ return mId; };

    private:
        ShaderType mType;
        GLuint mId, mProgramId;
    };
}