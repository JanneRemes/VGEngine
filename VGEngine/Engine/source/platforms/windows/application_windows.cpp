
#if defined(OS_WINDOWS)

#include "engine/application.h"
#include "engine/game/game.h"
#include "engine/graphics/graphics.h"
#include "engine/graphics/opengl.h"
#include "engine/input/keyboard.h"
#include "engine/graphics/screen.h"
#include "engine/input/mouse.h"
#include "engine/utility/timer.h"
#include <Windows.h>
#include <thread>
using namespace vg;
using namespace vg::core; 
using namespace vg::graphics; 
#ifndef CONF_DLL
extern void mainGame(Game *game);
#endif
#define GetCurrentDir _getcwd

Application::Application()
{

}

/*
void Application::initContext()
{

}
*/

void Application::drawFrame()
{

}

/*
void Application::mmessageCheck()
{

}
*/

int main()
{
	Game* game = Game::getInstance();
	Graphics *graphics = new Graphics();
	graphics->initialize();
	game->setFileManager();
	game->setGraphics(graphics);

	game->start();

	Application *app = new Application();
	vg::Timer updateTimer;
	updateTimer.restart();
	float updateRate =  1.0f/100.0f;
#ifndef CONF_DLL
	mainGame(game);
#endif
	gl::clearColor(Screen::getColor());
	gl::clear();
	graphics->swapBuffers();
	
	while (game->isRunning())
	{
		
			app->update();
			
		float currentTime = updateTimer.getCurrentTimeSeconds();
		float microTime = ((updateRate - currentTime) * 1000.0f * 1000.0f);
		//std::cout << microTime << std::endl;
		if (updateRate > currentTime)
			std::this_thread::sleep_for(std::chrono::microseconds((int)microTime));
		updateTimer.restart();
	}
}

void Application::update()
{
	Graphics *graphics = Game::getInstance()->getGraphics();
	GraphicsContext *context = graphics->getContext();
	MSG msg;

	while (PeekMessage(&msg, static_cast<HWND>(context->getWindowHandle()), NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	input::Keyboard::update();
	input::Mouse::update();
	gl::clear();
	gl::clearColor(Screen::getColor());
	Game::getInstance()->update();
	graphics->swapBuffers();
}

#endif
