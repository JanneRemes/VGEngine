
#pragma once

#include <jni.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "engine/android_native_app_glue.h"
#include "engine/assets/fileManager.h"

/// @todo Fix comments in this file

namespace vg
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
        void initialize(ANativeWindow* window);

        /**
        Desroys EGL and disables openGL attributes and buffers
        */
        void destroy();

        /**
        Swaps draw buffers in the current context
        */
        void swapBuffers();

        /**
        <description>
        @return width of current screen in pixels
        */
        EGLint getWidth();

        /**
        <description>
        @return height of current screen in pixels
        */
        EGLint getHeight();

		/**
		<description>
		@return returns mProgramId (opengl program id)
		*/

		GLuint getProgramId();




    private:
        /**
        intializes EGL context for current device
        @param window pointer to current devices window handle
        */
        void initializeEGL(ANativeWindow* window);

		/**
		Creates Opengl program and puts it in mProgramId
		*/
		void createGLProgram();

        /**
        links shaders, creates buffers,
        @todo not being used yet
        */
        void initializeOpenGL();

        EGLDisplay mDisplay;    ///< handle to devices display
        EGLSurface mSurface;    ///< handle to device surface
        EGLContext mContext;    ///< handle to device context

        EGLint mWidth, mHeight; ///< screen size in pixels

		GLuint mProgramId; //< opengl program id
    };
}
