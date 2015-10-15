
#include "engine/game.h"
#include "engine/utility/logger.h"
#include "engine/utility/timer.h"
using namespace vg;
Game *Game::mGame = nullptr;
Game* Game::getInstance()
{
	if (mGame == nullptr)
	{
		mGame = new Game();
	}
	return mGame;
}

Game::Game()
    : mIsRunning(true)
{
	initSceneManager();
	deltaTimer = new Timer();
	//sound::AudioManager AM;
}

Game::~Game()
{
	delete mSceneManager;
	mGame = nullptr;
}
void Game::initSceneManager()
{
	mSceneManager = new SceneManager();
}
void Game::update()
{
	float deltaTime = deltaTimer->restart();

	mSceneManager->update(deltaTime); //TODO add deltatime
	mAudioManager->update();
	
}

void Game::setGraphics(vg::graphics::Graphics *graphics)
{
	this->mGraphics = graphics;
}


bool Game::isRunning()
{
    return mIsRunning;
}

void Game::stop()
{
    mIsRunning = false;
}

void Game::start()
{
    mIsRunning = true;
}

SceneManager*  Game::getSceneManager()
{
	return mSceneManager;
}

void Game::addComponentSystem(Scene *scene, System *componentSystem)
{
	scene->getComponentSystemManager()->addSystem(componentSystem);
}

void Game::log(char* text)
{
	Log("vgengine", "%s", text);
}

vg::graphics::Graphics* Game::getGraphics()
{
	return mGraphics;
}

Factory *Game::getFactory()
{
	return mFactory;
}

core::FileManager *Game::getFileManager()
{
	return mFileManager;
}

sound::AudioManager *Game::getAudioManager()
{
	return mAudioManager;
}

void Game::setFileManager()
{
	mFileManager = new core::FileManager();
	mAudioManager = new sound::AudioManager();
	mAssetManager = new core::AssetManager(mFileManager);
	mFactory = new Factory(mAssetManager, mFileManager);
}

core::AssetManager* Game::getAssetManager()
{
	return mAssetManager;
}