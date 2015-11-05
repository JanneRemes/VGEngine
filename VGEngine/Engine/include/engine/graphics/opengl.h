
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
		Wrappers for opengl functions. GL errors are checked and printed after each call.
		*/
		namespace gl
		{
			void checkError();

			void enableVertexAttribArray(unsigned int index);

			void vertexAttribPointer(uint32_t index, int32_t size, int32_t stride, void* data);

			/**
			type = GL_FLOAT, normalized = GL_FALSE
			*/
			void vertexAttribPointer(unsigned int indx, int size, int stride, const void* ptr);

			void drawArrays(unsigned int primitiveType, int offset, int  count);

			void drawElements(unsigned int primitiveType, int  count, unsigned int indexType, const void *indices = nullptr);

			void useProgram(unsigned int programId = 0);

			void genTextures(unsigned int* textureIds, int  amount = 1);

			void bindTexture(unsigned int textureId);

			void activeTexture();

			void activeTexture(unsigned int textureIndex);

			void deleteTextures(int n, const unsigned int* textures);

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

			bool linkStatus(unsigned int program);

			unsigned int getUniformLocation(unsigned int program, std::string name);

			void bindBuffer(unsigned int target, unsigned int buffer);

			void deleteBuffers(int n, const unsigned int* buffers);

			void bufferData(unsigned int target, signed   long  int size, const void* data, unsigned int usage);

			void genBuffers(int n, unsigned int* buffers);

			void shaderSource(unsigned int shader, int count, const char** string, const int* length);

			void getShaderInfoLog(unsigned int shader, int bufsize, int* length, char* infolog);

			/**
			pname = GL_INFO_LOG_LENGTH
			*/
			void getShaderivInfoLog(unsigned int shader, int* params);

			/**
			pname = GL_COMPILE_STATUS
			*/
			bool getShaderivCompileStatus(unsigned int shader);

			unsigned int createProgram(void);

			/**
			type = GL_VERTEX_SHADER
			*/
			unsigned int createVertexShader();

			/**
			type = GL_FRAGMENT_SHADER
			*/
			unsigned int createFragmentShader();

			void bindAttribLocation(unsigned int program, unsigned int index, const char* name);

			void compileShader(unsigned int shader);
			
			unsigned int getGL_CLAMP_TO_EDGE();

			unsigned int getGL_COLOR_BUFFER_BIT();

			unsigned int getGL_ELEMENT_ARRAY_BUFFER();

			unsigned int getGL_LINEAR();

			unsigned int getGL_TEXTURE_MAG_FILTER();

			unsigned int getGL_TEXTURE_MIN_FILTER();

			unsigned int getGL_TEXTURE_WRAP_S();

			unsigned int getGL_TEXTURE_WRAP_T();

			unsigned int getGL_ALPHA();

			unsigned int getGL_DYNAMIC_DRAW();

			unsigned int getGL_ARRAY_BUFFER();

			unsigned int getGL_UNSIGNED_SHORT();

			unsigned int getGL_TRIANGLES();
			
			unsigned int getGL_NEAREST();

			unsigned int getGL_COMPILE_STATUS();
		}
	}
}
