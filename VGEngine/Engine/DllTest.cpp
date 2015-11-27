#include "DllTest.h"
#include "engine/application.h"
#include "engine/game/game.h"
#include "engine/graphics/graphics.h"
#include "engine/graphics/screen.h"
#include "engine/graphics/opengl.h"
#include "engine/game/scene.h"
#ifdef OS_WINDOWS
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#include "engine/utility/logger.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderComponent.h"
#include <direct.h>
using namespace vg;
using namespace vg::core;
using namespace vg::graphics;
Application *app;
#define GetCurrentDir _getcwd
extern "C" __declspec(dllexport) int __stdcall doubleValue(int value)
{
	std::cout << value * 2 << std::endl;
	return value * 2;
}

extern "C" __declspec(dllexport) int __stdcall combineNumbers(int value1, int value2)
{
	return value1 + value2;
}
extern "C" __declspec(dllexport) void __cdecl Add(int value)
{
	std::cout << value*value << std::endl;
}
extern "C"__declspec(dllexport) void __cdecl MakeGame(void *data)
{
	Game* game = Game::getInstance();
	Graphics *graphics = new Graphics();
	graphics->getContext()->mWindowHandle = data;
	graphics->initialize();
	game->setFileManager();
	game->setGraphics(graphics);

	game->start();

	app = new Application();
	gl::clearColor(Screen::getColor());
	gl::clear();
	graphics->swapBuffers();
	Scene *scene = new Scene();
	GameObject *gg = new GameObject("GG");
	gg->addComponent(new TransformComponent(Vec2f(0, 0),
		Vec2f(1280, 720), 0.0f));
	gg->addComponent(new RenderComponent("doge.png"));
	scene->addGameObject(gg);

	game->getSceneManager()->addTemplateScene("scene", scene);
	game->getSceneManager()->changeScene("scene");
	Screen::setColor(vg::Color(100, 100, 50));

}
extern "C"__declspec(dllexport) void __cdecl Update()
{
	app->update();
}
extern "C"__declspec(dllexport) int __stdcall Pointer(void *data)
{
	HWND doge = static_cast<HWND>(data);
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(doge, &pt);
	return pt.x;
}
#endif