#pragma once
#include <jni.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "engine\android_native_app_glue.h"

#define MLG(severity, message, ...) __android_log_print(ANDROID_LOG_DEBUG, severity, "%s, %d, %s: " message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)


class GraphicsContext
{
public:
    GraphicsContext();
    ~GraphicsContext();

    void initialize(ANativeWindow* window);
    void destroy();
    void swapBuffers();

    /**
     * @return width of current context in pixels
     */
    EGLint getWidth(){ return mWidth; };

    /**
    * @return height of current context in pixels
    */
    EGLint getHeight(){ return mHeight; };

    /**
    * @return has graphicsContext been initialized
    */
    bool isInitialized(){ return mInitialized; };

private:
    void initializeEGL(ANativeWindow* window);
    void initializeOpenGL();

    EGLDisplay mDisplay;
    EGLSurface mSurface;
    EGLContext mContext;

    EGLint mWidth, mHeight;
    //GLuint mProgramId, mVertexId, mFragmentId;
    //GLuint mBuffers[2];
    //GLint mPositionIndex;

    bool mInitialized;
};