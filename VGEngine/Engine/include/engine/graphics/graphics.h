
#pragma once

#include "engine/graphics/graphicsContext.h"
#include "engine/graphics/shader.h"
#include "engine/assets/fileManager.h"
#include <engine/utility/Vector2.h>

#include <string>
#include <vector>

namespace vg
{
	namespace graphics
	{
		class IndexBuffer;
		class VertexBuffer;

		/**
		Managing and initiliazing shaders and buffers
		*/
		class Graphics
		{
		public:
			/**
				Default constructor
				*/
			Graphics();

			/**
				<description>
				*/
			~Graphics();

			/**
				initializes FileManager, GraphicsContext and Shader
				@param app pointer to current Android application struct
				@param shader reference to Shader, uses Shader's default constructor as default
				*/
			void initialize( const Shader& shader = Shader());

			/**
				destroys GraphicsContext
				*/
			void unInitialize();

			/**
				@return true of Graphics has been initialized>
				*/
			bool isInitialized();

			/**
				Swaps drawbuffers in GraphicContext
				*/
			void swapBuffers();

			/**
				Loads and links new shader sources from disk
				@param vertexPath path to vertex shader source file
				@param fragmentPath path to fragment shader source file
				*/
			void switchShader(std::string vertexPath, std::string fragmentPath);

			/**
				@return pointer to current Shader
				*/
			Shader *getShader();

			/**
				@return pointer to current GraphicsContext
				*/
			GraphicsContext *getContext();

			/**
			Draw the content of the buffers
			@param vertices Vertexbuffer which vertices are used for the draw
			@param indices Indexbuffer which indices are used for the draw
			*/
			static void draw(Shader* shader, VertexBuffer* vertices, IndexBuffer* indices);

		private:
			core::FileManager* mFileManager;	///< pointer to FileManager
			GraphicsContext mContext;			///< current GraphicsContext
			Shader mShader;						///< current Shader
			bool mInitialized;					///< has Graphics been initialized
		};
	}
}