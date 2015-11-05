
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


			// draw
			void drawTriangles(int  count, const void *indices = nullptr);
			void clear();
			void clearColor(float red, float green, float blue, float alpha);			
			

			//texture
			void genTextures(unsigned int* textureIds, int  amount = 1);
			void bindTexture(unsigned int textureId);
			void activeTexture();
			void activeTexture(unsigned int textureIndex);
			void deleteTextures(int n, const unsigned int* textures);
			void texImage2DRGBA(unsigned int width, unsigned int height, const std::vector<unsigned char>& pixels);
			void texImage2DRGBA(unsigned int width, unsigned int height, const unsigned char* pixels);
			void texImage2DAlpha(unsigned int width, unsigned int height, const std::vector<unsigned char>& pixels);
			void texImage2DAlpha(unsigned int width, unsigned int height, const unsigned char* pixels);
			void texParameteri(unsigned int pname, int parameter);


			// shader uniforms
			void setUniform(unsigned int location, glm::mat3& value);
			void setUniform(unsigned int location, glm::mat4& value);
			void setUniform(unsigned int location, const float* value);
			void setUniform(unsigned int location, glm::vec2& value);
			void setUniform(unsigned int location, glm::vec3& value);
			void setUniform(unsigned int location, glm::vec4& value);
			unsigned int getUniformLocation(unsigned int program, std::string name);
			

			// shader attributes
			void bindAttribLocation(unsigned int program, unsigned int index, const char* name);


			//shader
			void useProgram(unsigned int programId = 0);
			unsigned int createProgram();
			void attachShader(unsigned int program, unsigned int shader);
			void linkProgram(unsigned int program);
			bool linkStatus(unsigned int program);
			void shaderSource(unsigned int shader, int count, const char** string, const int* length);
			void getShaderInfoLog(unsigned int shader, int bufsize, int* length, char* infolog);
			void getShaderivInfoLog(unsigned int shader, int* params);
			bool getShaderivCompileStatus(unsigned int shader);
			unsigned int createVertexShader();
			unsigned int createFragmentShader();
			void compileShader(unsigned int shader);


			//buffers
			void vertexAttribPointer(unsigned int index, int size, int stride, const void* ptr);
			void enableVertexAttribArray(unsigned int index);
			void bindBuffer(unsigned int target, unsigned int buffer);
			void deleteBuffers(int n, const unsigned int* buffers);
			void bufferData(unsigned int target, signed long int size, const void* data, unsigned int usage);
			void genBuffers(int n, unsigned int* buffers);
			void bufferSubData(unsigned int target, int offset, signed long int size, const void* data);
			
			///TODO remove
			unsigned int getGL_CLAMP_TO_EDGE();
			unsigned int getGL_LINEAR();
			unsigned int getGL_TEXTURE_MAG_FILTER();
			unsigned int getGL_TEXTURE_MIN_FILTER();
			unsigned int getGL_TEXTURE_WRAP_S();
			unsigned int getGL_TEXTURE_WRAP_T();
			unsigned int getGL_NEAREST();

			unsigned int getGL_ELEMENT_ARRAY_BUFFER();
			unsigned int getGL_ARRAY_BUFFER();
			unsigned int getGL_DYNAMIC_DRAW();
			unsigned int getGL_STATIC_DRAW();
		}
	}
}
