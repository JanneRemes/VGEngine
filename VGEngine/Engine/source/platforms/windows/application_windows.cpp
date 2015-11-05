
#if defined(OS_WINDOWS)

#include "engine/application.h"
#include "engine/game/game.h"
#include "engine/graphics/graphics.h"
#include "engine/graphics/opengl.h"
#include "engine/input/keyboard.h"

#include <Windows.h>

using namespace vg;
using namespace vg::core; 
using namespace vg::graphics; 
extern void mainGame(Game *game);
#define GetCurrentDir _getcwd

Application::Application()
{

}
void Application::initContext()
{

}
void Application::drawFrame()
{

}
void Application::mmessageCheck()
{

}

int main()
{
	Game* game = Game::getInstance();
	Graphics *graphics = new Graphics();
	graphics->initialize();
	game->setFileManager();
	game->setGraphics(graphics);

	game->start();

	Application *a = new Application();
	mainGame(game);
	gl::clearColor(0.7f, 0.2f, 0.1f, 1.0f);
	gl::clear();
	graphics->swapBuffers();
	while (game->isRunning())
	{
		a->update();
	}
}
void Application::update()
{
	vg::input::Keyboard::update();
	Graphics *graphics = Game::getInstance()->getGraphics();
	GraphicsContext *context = graphics->getContext(); 
	//Update window
	MSG msg;//I don't even...

	while (PeekMessage(&msg, static_cast<HWND>(context->mWindowHandle), NULL, NULL, PM_REMOVE))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//clear graphics
	gl::clearColor(0.7f, 0.2f, 0.1f, 1.0f);
	gl::clear();
	//gl::clearColor(vg::input::Input::getTouchX() / graphics->getScreenWidth(), 0.5f,
	//	(vg::input::Input::getTouchY()) / graphics->getScreenHeight(), 1);
	//Update game
	Game::getInstance()->update();
	//swap buffers
	graphics->swapBuffers();
}
#endif