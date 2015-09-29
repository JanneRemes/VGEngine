#if defined(OS_WINDOWS) //|| true == true
#include "engine\application.h"
#include "engine\game\game.h"
#include "engine\graphics\graphics.h"
#include "engine\input\input.h"
using namespace vg;
using namespace vg::core; 
using namespace vg::graphics; 
extern void mainGame(Game *game);

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
	while (game->isRunning())
	{
		a->update();
	}


}
void Application::update()
{
	vg::input::Input::update();
	Graphics *graphics = Game::getInstance()->getGraphics();
	gl::clear();
	gl::clearColor(vg::input::Input::getTouchX() / graphics->getScreenWidth(), 0.5f,
		(vg::input::Input::getTouchY()) / graphics->getScreenHeight(), 1);
	
	Game::getInstance()->update();

	graphics->swapBuffers();
}
#endif