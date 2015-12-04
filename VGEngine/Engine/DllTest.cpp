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
#include "engine/game/component.h"
#include <direct.h>
using namespace vg;
using namespace vg::core;
using namespace vg::graphics;
Application *app;
#define GetCurrentDir _getcwd
bool running = false;
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
	running = true;

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
extern "C"__declspec(dllexport) int __stdcall SendCommand(const char *data, char* returnData, int returnDataSize)
{
	
	if (!running)
		return -1;
	std::string parameters;
	//parameters
	//std::string getName = "GETNAMEGAMEOBJECT";
	//parameters = std::string(data).substr(getName.length()+1, string(data).length());
	//strcpy(returnData, parameters.c_str());
	Log("vgengine", "Start of method");

	command Command = getCommand(std::string(data), parameters);
	//strcpy(returnData, std::string(data).substr(0, getName.length()).c_str());
	switch (Command)
	{
		case CREATEGAMEOBJECT:
		{
			GameObject *newObject = new GameObject(parameters);
			Game::getInstance()->getSceneManager()->getActiveScene()->addGameObject(newObject);
			std::string returnString = "Object created" + newObject->getName();
			strcpy(returnData, returnString.c_str());
				break;
		}
		case GETIDGAMEOBJECT:
			break;
		case GETNAMEGAMEOBJECT:
		{
			Log("vgengine", "Getname");
			int id = stoi(parameters, nullptr, 10);
			GameObject *gg = GameObject::getGameObject(id);
			strcpy(returnData, gg->getName().c_str());
			break;
		}
		case GETNAMESGAMEOBJECTS:
		{
			std::string value;
			auto doge = GameObject::getGameObjects();
			for (int i = 0; i < doge->size(); i++)
			{
				if (i == doge->size() - 1)
				{
					value = value + doge->at(i)->getName();
					auto maggara = doge->at(i)->getAllComponents();
					for (auto it = maggara->begin(); it != maggara->end(); it++)
					{

						value = value + ";" + it->first->name();
					}
				}
				else
				{
					value = value + doge->at(i)->getName() + ",";
					auto maggara = doge->at(i)->getAllComponents();
					for (auto it = maggara->begin(); it != maggara->end(); it++)
					{
						
						value = value + ";" + it->first->name();
					}
				}
			}
			strcpy(returnData, value.c_str());
			break;
		}
	}
	return 1;
}
command getCommand(std::string command, std::string &returnData)
{
	std::string createObject = "CREATEGAMEOBJECT";
	std::string getId = "GETIDGAMEOBJECT";
	std::string getName = "GETNAMEGAMEOBJECT";
	std::string getNames = "GETNAMESGAMEOBJECTS";
	std::string value;
	//strcmp(command.substr(0, createObject.length()).c_str(), createObject.c_str()) == 0
	if (doesEqual(command, createObject, returnData))
	{
		//returnData = command.substr(createObject.length() + 1, string(command).length());
		return CREATEGAMEOBJECT;
	}
	else if (doesEqual(command, getId, returnData))
	{
		//returnData = command.substr(getId.length() + 1, string(command).length() == 0);
		return GETIDGAMEOBJECT;
	}
	else if (doesEqual(command,getName,returnData))
	{
		//returnData = command.substr(getName.length() + 1, string(command).length());
		return GETNAMEGAMEOBJECT;
	}
	else if (doesEqual(command, getNames, returnData))
	{
		//returnData = command.substr(getNames.length() + 1, string(command).length());
		return GETNAMESGAMEOBJECTS;
	}
	returnData = std::string("null");
	return NONE;
}
bool doesEqual(std::string original, std::string compareTo, std::string &returnData)
{
	returnData = original.substr(compareTo.length() + 1, string(original).length());
	return strcmp(original.substr(0, compareTo.length()).c_str(), compareTo.c_str()) == 0;
}
#endif