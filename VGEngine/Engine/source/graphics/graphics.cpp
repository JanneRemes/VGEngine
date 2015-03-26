
#include "engine/graphics/graphics.h"
#include "engine/utility/logger.h"

using namespace vg;
using namespace std;


Graphics::Graphics()
    : mInitialized(false)
{
}

Graphics::~Graphics()
{
    delete mFileManager;
    vector<SpriteBatch*>::iterator i;
    
    /*
    for (i = mBatches.begin(); i != mBatches.end(); i++)
    {
        delete (*i);
    }
    mBatches.clear();
    */
}

void Graphics::initialize(android_app* app, const Shader& shader)
{
    mFileManager = new FileManager(app);
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

/*
void Graphics::append(SpriteBatch* spriteBatch)
{
    mBatches.push_back(spriteBatch);
}
*/

void Graphics::draw()
{
    /// @todo draw spriteBatches
	/*
    vector<DebugSprite*>::iterator i;
    for (i = mDebugSprites.begin(); i != mDebugSprites.end(); i++)
    {
        (*i)->draw(mShader);
    }*/
}

void Graphics::append(DebugSprite* sprite)
{
    mDebugSprites.push_back(sprite);
}
