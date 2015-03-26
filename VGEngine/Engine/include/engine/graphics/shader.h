
#pragma once

#include "engine/assets/fileManager.h"
#include "engine/graphics/vertexBufferElement.h"

#include <GLES2/gl2.h>
#include <string>
#include <map>
#include <vector>

namespace vg
{
    /// A map containing the usage and name of vertex attributes
	typedef std::map<uint32_t, std::string> AttributeNameMap;

    /**
		Holds shader attribute and  ids and links itself
    */
    class Shader
    {
    public:
        /**
			Creates a shader with default or custom vertex element attribute names
			@param attributeNames map containing the usage and name of vertex attributes
        */
        Shader(const AttributeNameMap& attributeNames = getDefaultAttribNames());
        Shader(const Shader& shader);

        void initialize();

        bool isInitialized();

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
        const AttributeNameMap& getVertexElementNames();


    private:
        /**
			Returns default map of vertex element ids and names
			@return default map of vertex element usages and names
        */
        static AttributeNameMap getDefaultAttribNames();

        /**
			Compiles shader source code
			@return GL_TRUE if compile was succesful
        */
        GLint compileShaderSource(GLuint id, const std::string& source);

        void printErrorLog(GLuint shader);

        GLuint mVertexId;                          ///< vertex shader id used for linking
        GLuint mFragmentId;                        ///< fragment shader id used for linking
        GLuint mProgramId;                         ///< shader program id used for linking
        AttributeNameMap mVertexElementNames;      ///< map of vertex element ids and names
        bool mInitialized;
    };
}