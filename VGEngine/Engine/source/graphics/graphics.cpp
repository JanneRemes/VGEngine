
#include "engine/graphics/graphics.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"
#include "engine/application.h"
#include "engine\android_native_app_glue.h"
using namespace vg::graphics;
using namespace std;
using namespace vg::core;

Graphics::Graphics()
    : mInitialized(false)
{
}

Graphics::~Graphics()
{
    delete mFileManager;
}

void Graphics::initialize( const Shader& shader)
{
	android_app *app = static_cast<android_app*>(Application::getInstance()->getEngine());
    mFileManager = new core::FileManager();
    mContext.initialize();
    mShader = Shader(shader);
    mShader.load(*mFileManager);
	
    mInitialized = true;
}

void Graphics::unInitialize()
{
    mContext.destroy();
    mInitialized = false;
}

bool Graphics::isInitialized()
{
    return mInitialized;
}

void Graphics::swapBuffers()
{
    mContext.swapBuffers();
}

int Graphics::getScreenWidth()
{
    if (mInitialized)
        return mContext.getWidth();
    else
    {
        Log("vgengine", "Graphics context not initialized!", "");
        return 0;
    }
}

int Graphics::getScreenHeight()
{
    if (mInitialized)
        return mContext.getHeight();
    else
    {
        Log("vgengine", "Graphics context not initialized!", "");
        return 0;
    }
}

void Graphics::switchShader(string vertexPath, string fragmentPath)
{
    if (mInitialized)
        mShader.load(*mFileManager, vertexPath, fragmentPath);
    else
        Log("vgengine", "Graphics context not initialized!", "");
}

Shader* Graphics::getShader()
{
	return &mShader;
}

GraphicsContext* Graphics::getContext()
{
	return &mContext;
}

void Graphics::draw(Shader* shader, VertexBuffer* vertices, IndexBuffer* indices)
{
	vertices->bind();
	indices->bind();
	gl::drawElements(getGL_TRIANGLES(), vertices->getSize(), getGL_UNSIGNED_SHORT());
	indices->unbind();
	vertices->unbind();
}