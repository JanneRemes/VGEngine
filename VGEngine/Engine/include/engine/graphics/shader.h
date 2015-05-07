
#pragma once

#include "engine/assets/fileManager.h"
#include "engine/graphics/vertexBufferElement.h"
#include "engine/utility/Vector2.h"
#include "engine/graphics/uniformElement.h"
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
		typedef std::map<UniformUsage, UniformElement> UniformNames;

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
				const UniformNames& uniformNames = getDefaultUniformNames());

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
			bool load(FileManager& fileManager,
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
				Returns current map of vertex element ids and names
				@return map of vertex element ids and names
				*/
			const VariableNames& getVertexElementNames();

			/**
				Reset saved uniform values to defaults. They sent to be sent to GPU.
				*/
			void resetUniforms();

			/**
			   Set saved uniform value for position.
			   */
			void setPosition(vg::Vector2<int> position);

			/**
				Set saved uniform value for size.
				*/
			void setSize(vg::Vector2<int> size);

			/**
				Set saved uniform value for rotation in degrees increasing in clockwise direction.
				*/
			void setRotation(float degrees);

			/**
				Vertices with higher layer value will be drawn on top. Values above 28 will cause distortion.
				@param layer Layer value for next draw call
				*/
			void setLayer(uint layer);

			/**
				Send saved uniform values to GPU.
				*/
			void updateUniforms();

			/**
				Gets current screen size and sends new projection transform matrix to GPU
				*/
			void updateProjectionTransform();

            /**
                Set value to shader uniform boolean
                */
            void setUniformBoolean(std::string name, bool value);

		private:
			/**
				Returns default map of vertex element ids and names
				@return default map of vertex element usages and names
				*/
			static VariableNames getDefaultAttribNames();

			static UniformNames getDefaultUniformNames();

			/**
				Compiles shader source code
				@return GL_TRUE if compile was succesful
				*/
			GLint compileShaderSource(GLuint id, const std::string& source);

			/**
				Prints shader ShaderInfoLog to debug log
				*/
			void printErrorLog(GLuint shader);

			GLuint mVertexId;                          ///< Vertex shader id used for linking
			GLuint mFragmentId;                        ///< Fragment shader id used for linking
			GLuint mProgramId;                         ///< Shader program id used for linking
			VariableNames mVertexElementNames;         ///< Map of vertex element ids and names
			UniformNames mUniformNames;				   ///< Map of shader uniform ids and names
			bool mInitialized;                         ///< Have shaders been initialized

			glm::vec2 mPosition;                       ///< Position in pixels
			glm::vec2 mSize;						   ///< Size in pixels
			float mRotation;                           ///< Rotation clockwise in degrees
			float mLayer;                              ///< Layer for drawing ranging from 0 to 1
		};
	}
}