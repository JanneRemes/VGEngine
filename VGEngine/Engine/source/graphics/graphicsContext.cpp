
#include "engine/graphics/GraphicsContext.h"
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"

using namespace vg;

GraphicsContext::GraphicsContext()
{
    mWidth = mHeight = 0;
    mDisplay = mSurface = mContext = NULL;
}

GraphicsContext::~GraphicsContext()
{

}

void GraphicsContext::initialize(ANativeWindow* window)
{
    initializeEGL(window);
	initializeOpenGL();
}

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
}

void GraphicsContext::swapBuffers()
{
    eglSwapBuffers(mDisplay, mSurface);
}

GLint GraphicsContext::getWidth()
{
    return mWidth;
}

GLint GraphicsContext::getHeight()
{
    return mHeight;
}

void GraphicsContext::initializeEGL(ANativeWindow* window)
{
	EGLint attribs[] = 
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_DEPTH_SIZE, 16,
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
    {
        Log("WARNING", "Unable to eglMakeCurrent", "");
    }

    eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mWidth);
    eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mHeight);
}

void GraphicsContext::createGLProgram()
{
	mProgramId = glCreateProgram();
}

void GraphicsContext::initializeOpenGL()
{
	gl::checkError();

	// transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// z-layer
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDepthRangef(0.0, 1.0);

	// font
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	gl::checkError();
}

GLuint GraphicsContext::getProgramId()
{
	return mProgramId;
}