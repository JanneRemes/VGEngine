
#include "engine/graphics/graphics.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"

using namespace vg::graphics;
using namespace std;


Graphics::Graphics()
    : mInitialized(false)
{
}

Graphics::~Graphics()
{
    delete mFileManager;
}

void Graphics::initialize(android_app* app, const Shader& shader)
{
    mFileManager = new core::FileManager(app);
    mContext.initialize(app->window);
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
        Log("ERROR", "Graphics context not initialized!", "");
        return 0;
    }
}

int Graphics::getScreenHeight()
{
    if (mInitialized)
        return mContext.getHeight();
    else
    {
        Log("ERROR", "Graphics context not initialized!", "");
        return 0;
    }
}

void Graphics::switchShader(string vertexPath, string fragmentPath)
{
    if (mInitialized)
        mShader.load(*mFileManager, vertexPath, fragmentPath);
    else
        Log("ERROR", "Graphics context not initialized!", "");
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
	gl::drawElements(GL_TRIANGLES, vertices->getSize(), GL_UNSIGNED_SHORT);
	indices->unbind();
	vertices->unbind();
}