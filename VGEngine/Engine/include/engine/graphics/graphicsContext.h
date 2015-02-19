
#pragma once

#include <jni.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "engine\android_native_app_glue.h"
#include "engine/assets/fileManager.h"

/// @todo Use the dedicated logger instead
#define Log(severity, message, ...) __android_log_print(ANDROID_LOG_DEBUG, severity, "%s, %d, %s: " message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

/// @todo Fix comments in this file

namespace vg
{
	/**
		<description>
	*/
    class GraphicsContext
    {
    public:
		/**
			<description>
		*/
        GraphicsContext();

        ~GraphicsContext();

		/**
			<description>
			@param window <description>
		*/
        void initialize(ANativeWindow* window);

		/**
			<description>
		*/
        void destroy();

		/**
			<description>
		*/
        void swapBuffers();

		/// @todo Move function implementation to the .cpp file
		/**
			<description>
			@return width of current context in pixels
		*/
        EGLint getWidth()
		{
			return mWidth;
		}

		/// @todo Move function implementation to the .cpp file
		/**
			<description>
			@return height of current context in pixels
		*/
        EGLint getHeight()
		{
			return mHeight;
		}

		/// @todo Move function implementation to the .cpp file
		/**
			<description>
			@return has graphicsContext been initialized
		*/
        bool isInitialized()
		{
			return mInitialized;
		}

    private:
		/**
			<description>
			@param window <description>
		*/
        void initializeEGL(ANativeWindow* window);

		/**
			<description>
		*/
        void initializeOpenGL();

        EGLDisplay mDisplay;    ///< description
        EGLSurface mSurface;    ///< description
        EGLContext mContext;    ///< description

        EGLint mWidth, mHeight; ///< description
        bool mInitialized;      ///< description
    };
}
