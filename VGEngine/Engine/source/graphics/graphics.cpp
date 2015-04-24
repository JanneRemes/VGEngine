
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
    
	for (vector<DebugSprite*>::iterator i = mDebugSprites.begin(); i != mDebugSprites.end(); i++)
		delete (*i);
	mDebugSprites.clear();
}

void Graphics::initialize(android_app* app, const Shader& shader)
{
    mFileManager = new FileManager(app);
    mContext.initialize(app->window);
    mShader = Shader(shader);
    mShader.load(*mFileManager);

   // std::string fontpath = "font.ttf";
	//t = new text(fontpath, mFileManager);

    mInitialized = true;

	for (vector<DebugSprite*>::iterator i = mUnloadedDebugSprites.begin(); i != mUnloadedDebugSprites.end(); i++)
	{
		(*i)->getTexture()->load(mFileManager);
		(*i)->initialize();
		mDebugSprites.push_back(*i);
	}
	mUnloadedDebugSprites.clear();

	//char X = 'X';
	//t->initialize();

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

void Graphics::draw()
{
	if (mInitialized)
	{
		/// @todo draw spriteBatches
		vector<DebugSprite*>::iterator i;
		for (i = mDebugSprites.begin(); i != mDebugSprites.end(); i++)
		{
			(*i)->draw(mShader);
		}
   //     t->draw(mShader);
	}
	else
		Log("ERROR", "Graphics context not initialized!", "");

}

void Graphics::append(DebugSprite* sprite)
{
	if (mInitialized)
		mDebugSprites.push_back(sprite);
	else
		mUnloadedDebugSprites.push_back(sprite);
}
