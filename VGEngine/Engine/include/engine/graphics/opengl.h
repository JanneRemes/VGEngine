
#pragma once


#include <stdint.h>
#include <vector>
#include <string>
#include "../external/glm/gtc/type_ptr.hpp"

namespace vg
{
	namespace graphics
	{
		/**
			Wrappers for opengl functions. Errors are checked and printed to LogCat.
			*/
		namespace gl
		{
			/*class unsigned int;
			class unsigned int;
			class int ;
			class int;
			class void;
			class float;
			class float;*/
			void checkError();

			void vertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data);

			void drawArrays(unsigned int primitiveType, int offset, int  count);

			void drawElements(unsigned int primitiveType, int  count, unsigned int indexType, const void *indices = nullptr);

			void useProgram(unsigned int programId = 0);

			void genTextures(unsigned int* textureIds, int  amount = 1);

			void bindTexture(unsigned int textureId);

			void activeTexture();

			void activeTexture(unsigned int textureIndex);

			void texImage2D(unsigned int width, unsigned int height, const std::vector<unsigned char>& pixels);

			void texImage2D(unsigned int width, unsigned int height, const std::vector<unsigned char>& pixels, unsigned int format);

			void texImage2D(unsigned int width, unsigned int height, const unsigned char* pixels, unsigned int format);

			void texParameteri(unsigned int pname, int parameter);

			void clear();

			void clearColor(float red, float green, float blue, float alpha);

			void setUniform(unsigned int location, glm::mat3& value);

			void setUniform(unsigned int location, glm::mat4& value);

			void setUniform(unsigned int location, const float* value);

			void setUniform(unsigned int location, glm::vec2& value);

			void setUniform(unsigned int location, glm::vec3& value);

			void setUniform(unsigned int location, glm::vec4& value);

			void attachShader(unsigned int program, unsigned int shader);

			void linkProgram(unsigned int program);

			int linkStatus(unsigned int program);

			unsigned int getUniformLocation(unsigned int program, std::string name);
		}
	}
}
