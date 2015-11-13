
#if defined(OS_WINDOWS)

#include "engine/application.h"
#include "engine/game/game.h"
#include "engine/graphics/graphics.h"
#include "engine/graphics/opengl.h"
#include "engine/input/keyboard.h"
#include "engine/graphics/screen.h"
#include "engine/input/mouse.h"

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

	Application *app = new Application();
	mainGame(game);
	gl::clearColor(Screen::getRed(), Screen::getGreen(), Screen::getBlue(), Screen::getAlpha());
	gl::clear();
	graphics->swapBuffers();
	while (game->isRunning())
	{
		app->update();
	}
}

void Application::update()
{
	Graphics *graphics = Game::getInstance()->getGraphics();
	GraphicsContext *context = graphics->getContext();
	MSG msg;

	while (PeekMessage(&msg, static_cast<HWND>(context->mWindowHandle), NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	input::Keyboard::update();
	input::Mouse::update();
	gl::clear();
	gl::clearColor(Screen::getRed(), Screen::getGreen(), Screen::getBlue(), Screen::getAlpha());
	Game::getInstance()->update();
	graphics->swapBuffers();
}

#endif
