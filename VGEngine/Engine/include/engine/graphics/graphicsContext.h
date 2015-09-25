
#pragma once

#include <jni.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "engine/android_native_app_glue.h"
#include "engine/assets/fileManager.h"

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
			void initialize(void *windowHandle/*ANativeWindow* window*/);

			/**
			Desroys EGL and disables openGL attributes and buffers
			*/
			void destroy();

			/**
			Swaps draw buffers in the current context
			*/
			void swapBuffers();

			/**
			@return width of current screen in pixels
			*/
			EGLint getWidth();

			/**
			@return height of current screen in pixels
			*/
			EGLint getHeight();

			/**
			@return returns mProgramId (opengl program id)
			*/
			GLuint getProgramId();

		private:
			/**
			Initializes EGL context for current device
			@param window pointer to current devices window handle
			*/
			void initializeEGL(ANativeWindow* window);

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

			EGLDisplay mDisplay;    ///< Handle to devices display
			EGLSurface mSurface;    ///< Handle to device surface
			EGLContext mContext;    ///< Handle to device context

			EGLint mWidth, mHeight; ///< Screen size in pixels

			GLuint mProgramId; //< OpenGL program id
		};
	}
}
