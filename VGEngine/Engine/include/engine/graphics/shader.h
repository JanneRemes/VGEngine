
#pragma once

#include <GLES2\gl2.h>
#include <string>

/// @todo Fix comments in this file

namespace vg
{
    /**
    supported shader types
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

        /**
            <description>
            @return shaders own id used for linking
        */
        GLuint getId();

    private:
        ShaderType mType;  ///< shaders type
        GLuint mId;        ///< shaders own id used for linking
        GLuint mProgramId; ///< shader program id used for linking
    };
}