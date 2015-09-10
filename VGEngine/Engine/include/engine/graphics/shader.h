
#pragma once

#include "engine/assets/fileManager.h"
#include "engine/graphics/vertexBufferElement.h"
#include "engine/utility/Vector2.h"
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtx/transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"

#include <GLES2/gl2.h>
#include <string>
#include <map>
#include <vector>

namespace vg
{
	namespace graphics
	{
		/// A map containing the usage and name of vertex attributes
		typedef std::map<uint32_t, std::string> VariableNames;

		/**
			Holds shader attribute and  ids and links itself
			*/
		class Shader
		{
		public:
			/**
				Creates a shader with default or custom vertex element attribute names
				@param attributeNames map containing the usage and name of vertex attributes
				@param attributeNames map containing the usage and name of unifrom variables
				*/
			Shader(const VariableNames& attributeNames = getDefaultAttribNames(),
				const std::vector<std::string>& uniformNames = getDefaultUniformNames());

			/**
				Uninitializes and unloads everything.
				*/
			~Shader();

			/**
				Initialize values needed by load(). Don't call before GraphicsContext is initialized.
				*/
			void initialize();

			/**
				@return true if Shader has been initialized
				*/
			bool isInitialized();

			/**
				Loads and compiles shader sources from assets
				@param fileManager reference to an initialized FileManager
				@param vertexPath path to glsl file containing vertex shader source
				@param fragmentPath path to glsl file containing fragment shader source
				@return was shader source loading succesful
				*/
			bool load(core::FileManager& fileManager,
				const std::string& vertexPath = "default_vertex.glsl",
				const std::string& fragmentPath = "default_fragment.glsl");

			/**
				Returns current shader program id
				@return shader program id
				*/
			GLuint getProgramId();

			/**
				calls glUseProgram
				*/
			void useProgram();

			/**
				calls glUseProgram(0u)
				*/
			void unUseProgram();

			/**
				@return map of vertex element ids and names
				*/
			const VariableNames& getVertexElementNames();

			/**
				@return map of uniform variable names and usages
				*/
			const std::vector<std::string>& getUniformNames();

			/**
				Set uniform matrix value
				*/
			void setUniform(std::string name, glm::mat3 value);

			/**
				Set uniform matrix value
				*/
			void setUniform(std::string name, glm::mat4 value);

			/**
				Set uniform float value
				*/
			void setUniform(std::string name, float value);

            /**
                Set value to shader uniform boolean
                */
            void setUniform(std::string name, bool value);

			/**
				Set uniform vector values
				*/
			void setUniform(std::string name, glm::vec2 value);
			
			/**
				Set uniform vector values
				*/
			void setUniform(std::string name, glm::vec3 value);
			
			/**
				Set uniform vector values
				*/
			void setUniform(std::string name, glm::vec4 value);

		private:
			/**
				@return default map of vertex element usages and names
				*/
			static VariableNames getDefaultAttribNames();

			/**
				@return Vector of default uniform variable names
				*/
			static std::vector<std::string> getDefaultUniformNames();

			/**
				Compiles shader source code
				@return GL_TRUE if compile was succesful
				*/
			GLint compileShaderSource(GLuint id, const std::string& source);

			/**
				Prints shader ShaderInfoLog to debug log
				*/
			void printErrorLog(GLuint shader);

			GLuint mVertexId;								///< Vertex shader id used for linking
			GLuint mFragmentId;								///< Fragment shader id used for linking
			GLuint mProgramId;								///< Shader program id used for linking
			VariableNames mVertexElementNames;				///< Map of vertex element ids and names
			std::vector<std::string> mUniformNames;						///< list of uniform variable names
			std::map<std::string, GLuint> mUniformLocations;///< Map of shader uniform names and locations
			bool mInitialized;								///< Have shaders been initialized
		};
	}
}