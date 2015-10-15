
#include "engine/graphics/graphics.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"
#include "engine/application.h"
#include <engine/graphics/camera.h>

using namespace std;
using namespace glm;
using namespace vg;
using namespace vg::core;
using namespace vg::graphics;

Vector2<int> Graphics::mResolution = Vector2<int>(0, 0);

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

void Graphics::setResolution(Vector2<int> resolution)
{
	mResolution = resolution;
}

Vector2<int> Graphics::getResolution()
{
	return mResolution;
}

Vector2<float> Graphics::screenToWorld(float x, float y)
{
	Vector2<int> screen = Graphics::getResolution();
	Vector2<float> lt = Camera::getLeftTop();
	Vector2<float> rb = Camera::getRightBottom();
	float width = rb.getX() - lt.getX();
	float height = rb.getY() - lt.getY();
	return lt + Vector2<float>(x * (width / screen.getX()), y * (height / screen.getY()));
}

Vector2<float> Graphics::screenToWorld(Vector2<float> input)
{
	return screenToWorld(input.getX(), input.getY());
}