#include "engine\graphics\GraphicsContext.h"


GraphicsContext::GraphicsContext()
{
}

GraphicsContext::~GraphicsContext()
{

}

/**
 * Initializes EGL and openGL
 * @param window pointer to Android window mSurface
 */
void GraphicsContext::initialize(ANativeWindow* window)
{
    initializeEGL(window);

    // not used yet
    //initializeOpenGL(); 
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

    //glDisableVertexAttribArray(mPositionIndex);
    //glDeleteBuffers(2, mBuffers);
}


void GraphicsContext::swapBuffers()
{
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
    {
        MLG("WARNING", "Unable to eglMakeCurrent", "");
    }

    eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mWidth);
    eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mHeight);
}


void GraphicsContext::initializeOpenGL()
{
    /*
    GLint result = 0;
    mProgramId = glCreateProgram();
    mVertexId = glCreateShader(GL_VERTEX_SHADER);
    mFragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    // compile shader
    glShaderSource(mFragmentId, 1, &FRAGMENT_SOURCE, NULL);
    glShaderSource(mVertexId, 1, &VERTEX_SOURCE, NULL);
    glCompileShader(mVertexId);
    glCompileShader(mFragmentId);

    // shader compile errors
    glGetShaderiv(mVertexId, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
        LOGW("W", "Vertex shader compile error!");
    glGetShaderiv(mFragmentId, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
        LOGW("W", "Fragment shader compile error!");

    // link program
    glAttachShader(mProgramId, mVertexId);
    glAttachShader(mProgramId, mFragmentId);
    glLinkProgram(mProgramId);
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &result);
    if (result != GL_TRUE)
        LOGW("W", "Shader program link error!");

    //shader attributes
    mPositionIndex = glGetAttribLocation(mProgramId, "attrPosition");
    if (mPositionIndex < 0)
        LOGW("W", "Attribute: positionIndex not found!");
    glEnableVertexAttribArray(mPositionIndex);

    // create vertex and index buffers
    glGenBuffers(2, mBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(GLfloat), VERTEX_DATA, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0u);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), INDEX_DATA, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
    */
}