
#include "engine/graphics/GraphicsContext.h"
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"

using namespace vg::graphics;

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
	const EGLint config16bpp[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_NONE
	};

	const EGLint config24bpp[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_NONE
	};

	const EGLint config32bpp[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 16,
		EGL_STENCIL_SIZE, 0,
		EGL_NONE
	};

    EGLint contextAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

	EGLint format, majorVersion, minorVersion, numConfigs, windowFormat;
	const EGLint* attribs = NULL;
    EGLConfig config;
    mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(mDisplay, &majorVersion, &minorVersion);
	Log("vgengine", "EGL version: %i.%i", majorVersion, minorVersion);
	checkError();

	windowFormat = ANativeWindow_getFormat(window);
	switch (windowFormat) 
	{
	case WINDOW_FORMAT_RGBA_8888:
		attribs = config32bpp;
		Log("vgengine", "Window format: 32 bits per pixel", "");
		break;
	case WINDOW_FORMAT_RGBX_8888:
		attribs = config24bpp;
		Log("vgengine", "Window format: 24 bits per pixel", "");
		break;
	case WINDOW_FORMAT_RGB_565:
		attribs = config16bpp;
		Log("vgengine", "Window format: 16 bits per pixel", "");
		break;
	default:
		attribs = config16bpp;
		Log("vgengine", "Unknown window format!", "");
	}

    eglChooseConfig(mDisplay, attribs, &config, 1, &numConfigs);
	Log("vgengine", "Number of EGL configs: %i", numConfigs);
	checkError();
	eglGetConfigAttrib(mDisplay, config, EGL_NATIVE_VISUAL_ID, &format);
	checkError();

    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

	mContext = eglCreateContext(mDisplay, config, NULL, contextAttribs);
	checkError();
    mSurface = eglCreateWindowSurface(mDisplay, config, window, NULL);
	checkError();

    if (eglMakeCurrent(mDisplay, mSurface, mSurface, mContext) == EGL_FALSE)
    {
        Log("vgengine", "Unable to eglMakeCurrent", "");
    }
	checkError();

    eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mWidth);
	checkError();
	eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mHeight);
	checkError();
}

void GraphicsContext::createGLProgram()
{
	mProgramId = glCreateProgram();
	gl::checkError();
}

void GraphicsContext::initializeOpenGL()
{
	const GLubyte* glVersion = glGetString(GL_VERSION);
	Log("vgengine", "OpenGL ES version: %s", glVersion);
	gl::checkError();

	// transparency
	glEnable(GL_BLEND);
	gl::checkError();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gl::checkError();

	// z-layer
	glEnable(GL_DEPTH_TEST);
	gl::checkError();
	glEnable(GL_CULL_FACE);
	gl::checkError();
	glCullFace(GL_BACK);
	gl::checkError();
	glFrontFace(GL_CCW);
	gl::checkError();
	glDepthFunc(GL_LESS);
	gl::checkError();
	glDepthMask(GL_TRUE);
	gl::checkError();
	glDepthRangef(0.0, 1.0);
	gl::checkError();

	// font
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	gl::checkError();
}

GLuint GraphicsContext::getProgramId()
{
	return mProgramId;
}

void GraphicsContext::checkError()
{
	EGLint error = eglGetError();
	if (error != EGL_SUCCESS)
	{
		Log("vgengine", "EGL error: %i", error, "");
	}
}