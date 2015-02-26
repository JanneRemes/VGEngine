
#pragma once

#include "engine\assets\fileManager.h"

#include <GLES2\gl2.h>
#include <string>
#include <map>

/// @todo finish comments in this file

namespace vg
{
    /// <description>
    enum VertexElementUsage
    {
        POSITION,
        COLOR,
        UV
    };

    /// Type for map containing vertex element ids and names
    typedef std::map<VertexElementUsage, std::string> NamesMap;

    /**
    Holds shader attribute and  ids and links itself
    @todo add map of shader attribute names and ids
    */
    class Shader
    {
    public:
        /**
        <description>
        @param fileManager <description>
        @param attributeNames map of vertex element usages and names
        @param vertexPath path to glsl file containing vertex shader source
        @param fragmentPath path to glsl file containing fragment shader source
        */
        Shader(NamesMap attributeNames = getDefaultAttribNames(),
            const std::string& vertexPath = "default_vertex.glsl",
            const std::string& fragmentPath = "default_fragment.glsl");

        /**
        <description>
        */
        ~Shader();


        /**
        <description>
        @return was shader source loading succesful
        */
        bool load(FileManager& fileManager);


        /**
            <description>
            @return shader program id
        */
        GLuint getProgramId();

    private:
        /**
        <description>
        @return default map of vertex element usages and names
        */
        static NamesMap getDefaultAttribNames();

        /**
        <description>
        @return GL_TRUE if compile was succesful
        */
        GLint compileShaderSource(GLuint id, std::string source);
        
        const std::string mSubFolder = "shaders/"; ///< subfolder for shader sources
        GLuint mVertexId;                          ///< vertex shader id used for linking
        GLuint mFragmentId;                        ///< fragment shader id used for linking
        GLuint mProgramId;                         ///< shader program id used for linking
        std::string mVertexPath;                   ///< vertex source path
        std::string mFragmentPath;                 ///< shader program id used for linking
        NamesMap mVertexElementNames;              ///< map of vertex element ids and names
    };
}