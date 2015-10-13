
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

Vector2<float> Graphics::translateInput(Vector2<float> input)
{
	float zoom = Camera::getZoom();
	vec2 camera(Camera::getPosition().getX(), Camera::getPosition().getY());
	vec2 screen(Graphics::getResolution().getX(), Graphics::getResolution().getY());
	vec4 result(input.getX(), input.getY(), 0.0f, 0.0f);

	/*
	mat4 transform = mat4();
	transform = translate(transform, vec3(0.5f * screen, 0.0f));
	transform = rotate(transform, Camera::getRotation(), vec3(0.0f, 0.0f, 1.0f));
	transform = translate(transform, vec3(-0.5f * screen, 0.0f));
	result = transform * result;
	*/
	result += vec4(camera, 0.0f, 0.0f);
	return Vector2<float>(result.x, result.y);
}