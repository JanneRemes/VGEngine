
#pragma once

#include "engine\assets\fileManager.h"

#include <GLES2\gl2.h>
#include <string>
#include <map>

namespace vg
{
    /// Shader attribute usage types
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
        Creates a shader with default or custom vertex element attribute names
        @param attributeNames map of vertex element usages and names
        */
        Shader(NamesMap attributeNames = getDefaultAttribNames());


        /**
        Loads and compiles shader sources from assets
        @param fileManager reference to an initialized FileManager
        @param vertexPath path to glsl file containing vertex shader source
        @param fragmentPath path to glsl file containing fragment shader source
        @return was shader source loading succesful
        */
        bool load(FileManager& fileManager,
            const std::string& vertexPath = "default_vertex.glsl",
            const std::string& fragmentPath = "default_fragment.glsl");


        /**
        Returns current shader program id
        @return shader program id
        */
        GLuint getProgramId();

        /**
        Returns current map of vertex element ids and names
        @return map of vertex element ids and names
        */
        const NamesMap& getmVertexElementNames();


    private:
        /**
        Returns default map of vertex element ids and names
        @return default map of vertex element usages and names
        */
        static NamesMap& getDefaultAttribNames();

        /**
        Compiles shader source code
        @return GL_TRUE if compile was succesful
        */
        GLint compileShaderSource(GLuint id, std::string source);
        
        const std::string mSubFolder = "shaders/"; ///< subfolder for shader sources
        GLuint mVertexId;                          ///< vertex shader id used for linking
        GLuint mFragmentId;                        ///< fragment shader id used for linking
        GLuint mProgramId;                         ///< shader program id used for linking
        NamesMap mVertexElementNames;              ///< map of vertex element ids and names
    };
}