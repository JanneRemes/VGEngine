
#pragma once
#include "../DllTest.h"
namespace vg
{
	namespace graphics
	{
		/**
		Initializes EGL and openGL, swaps buffers
		*/
		
		class GraphicsContext
		{
		public:
			/**
			Initializes default values
			*/
			GraphicsContext();

			~GraphicsContext();

			/**
			Initializes EGL and openGL and creates opengl program
			@param window pointer to Android window surface
			*/
			void initialize(/*ANativeWindow* window*/);

			/**
			Desroys EGL and disables openGL attributes and buffers
			*/
			void destroy();

			/**
			Swaps draw buffers in the current context
			*/
			void swapBuffers();

			/**
			@return returns mProgramId (opengl program id)
			*/
			unsigned int getProgramId();

			/**
			Used for windows sided window handling
			*/
			void* getWindowHandle();

			void* mWindowHandle;	///< HWND pointer to a window
		private:
			/**
			Initializes EGL context for current device
			@param window pointer to current devices window handle 
			*/
			void initializeGraphicsContext();

			/**
			Creates Opengl program and puts it in mProgramId
			*/
			void createGLProgram();

			/**
			links shaders, creates buffers
			*/
			void initializeOpenGL();
			/**
			Checks and prints possible EGL errors
			*/
			void checkError();



		};
	}
}
