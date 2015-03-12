
#include "engine/game.h"
#include "engine/utility/logger.h"
#include "engine/input/input.h"

using namespace vg;

Game::Game()
    : mPulse(0)
{
}


void Game::update()
{
    mPulse += .01f;
    if (mPulse > 1)
    {
        mPulse = 0;
    }
}


void Game::draw(GraphicsContext* graphicsContext)
{
    if (!graphicsContext->isInitialized())
    {
        Log("WARNING", "GraphicsContext not initialized", "");
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(Input::getX() / graphicsContext->getWidth(), mPulse,
        (Input::getY()) / graphicsContext->getHeight(), 1);
}


void readFiles(FileManager& fileManager)
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
        Log("fm", "success? %s", fileManager.writeFile(FileManager::Internal, file, str) ? "true" : "false");
        Log("fm", "line = '%s'", str.c_str());

        str = "";
        Log("fm", "Reading...", "");
        Log("fm", "success? %s", fileManager.readFile(FileManager::Internal, file, str) ? "true" : "false");
        Log("fm", "line = '%s'", str.c_str());
    }
    Log("fm", "End", "");
    Log("-----", "----- -----", "");
}

