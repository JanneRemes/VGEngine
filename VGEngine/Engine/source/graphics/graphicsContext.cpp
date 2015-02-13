#include "engine\graphics\GraphicsContext.h"
using namespace vg;

GraphicsContext::GraphicsContext()
{
    mInitialized = false;
    mWidth = mHeight = 0;
    mDisplay = mSurface = mContext = NULL;
}

GraphicsContext::~GraphicsContext()
{

}

/**
 * Initializes EGL and openGL
 * @param window pointer to Android window surface
 */
void GraphicsContext::initialize(ANativeWindow* window)
{
    if (!mInitialized)
    {
        initializeEGL(window);
        //initializeOpenGL(); // not used yet
        mInitialized = true;
    }
}


/**
 * Desroys EGL and disables openGL attributes and buffers
 */
void GraphicsContext::destroy()
{
    if (mDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_SURFACE);
        if (mContext != EGL_NO_CONTEXT)
        {
            eglDestroyContext(mDisplay, mContext);
        }
        if (mSurface != EGL_NO_SURFACE)
        {
            eglDestroySurface(mDisplay, mSurface);
        }
        eglTerminate(mDisplay);
    }

    mDisplay = EGL_NO_DISPLAY;
    mContext = EGL_NO_CONTEXT;
    mSurface = EGL_NO_SURFACE;

    mInitialized = false;
}


/**
 * Swaps draw buffers in the current context
 */
void GraphicsContext::swapBuffers()
{
    if (mInitialized)
        eglSwapBuffers(mDisplay, mSurface);
}


void GraphicsContext::initializeEGL(ANativeWindow* window)
{
    const EGLint attribs[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLint contextAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLint dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(mDisplay, 0, 0);
    eglChooseConfig(mDisplay, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(mDisplay, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    mSurface = eglCreateWindowSurface(mDisplay, config, window, NULL);
    mContext = eglCreateContext(mDisplay, config, NULL, contextAttribs);

    if (eglMakeCurrent(mDisplay, mSurface, mSurface, mContext) == EGL_FALSE)
        Log("WARNING", "Unable to eglMakeCurrent", "");

    eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mWidth);
    eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mHeight);
}


void GraphicsContext::initializeOpenGL()
{
}
