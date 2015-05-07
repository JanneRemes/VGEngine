
#include "engine/graphics/graphics.h"
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

    std::string fontpath = "arial.ttf";
	testText = new Text(fontpath, mFileManager);
	testText->setFontSize(16);
	testText->setText("Hello Miika");
	
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

void Graphics::draw()
{
	if (mInitialized)
	{
		vector<DebugSprite*>::iterator i;
		for (i = mDebugSprites.begin(); i != mDebugSprites.end(); i++)
		{
			(*i)->draw(&mShader);
		}
		testText->setPosition(testText->getPosition().getX(), testText->getPosition().getY() + 5);
		if (testText->getPosition().getY() > 720)
		{
			testText->setText("moi doge");
			testText->setColour(255, 0, 0);
            testText->setPosition(0, 0);

		}
        testText->draw(&mShader);
	}
	else
		Log("ERROR", "Graphics context not initialized!", "");
}

void Graphics::append(DebugSprite* sprite)
{
	mDebugSprites.push_back(sprite);
	sprite->getTexture()->load(mFileManager);
}

Shader* Graphics::getShader()
{
	return &mShader;
}

GraphicsContext* Graphics::getContext()
{
	return &mContext;
}
