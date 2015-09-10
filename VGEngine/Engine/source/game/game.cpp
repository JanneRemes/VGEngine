
#include "engine/game.h"
#include "engine/utility/logger.h"
#include "engine/input/input.h"
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

void readFiles(core::FileManager& fileManager)
{
    Log("-----", "----- -----", "");
    Log("fm", "Begin", "");
    {
        char buffer[1024];
        getcwd(buffer, sizeof(buffer));
        Log("fm", "path = '%s'", buffer);
        const std::string file = "test.txt";

        std::string str;

        str = "Hello World!";
        Log("fm", "Writing...", "");
        Log("fm", "success? %s", fileManager.writeFile(core::FileManager::Internal, file, str) ? "true" : "false");
        Log("fm", "line = '%s'", str.c_str());

        str = "";
        Log("fm", "Reading...", "");
        Log("fm", "success? %s", fileManager.readFile(core::FileManager::Internal, file, str) ? "true" : "false");
        Log("fm", "line = '%s'", str.c_str());
    }
    Log("fm", "End", "");
    Log("-----", "----- -----", "");
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
	scene->getObjectPool()->getComponentSystemManager()->addSystem(componentSystem);
}

void Game::log(char* text)
{
	Log("fm", "%s", text);
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

void Game::setFileManager(android_app *app)
{
	mFileManager = new core::FileManager(app);
	mAudioManager = new sound::AudioManager();
	mAssetManager = new core::AssetManager(mFileManager);
	mFactory = new Factory(mAssetManager, mFileManager);
}

core::AssetManager* Game::getAssetManager()
{
	return mAssetManager;
}