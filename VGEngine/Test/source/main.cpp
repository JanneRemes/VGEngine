
#include <engine/game/game.h>
#include <engine/game/SceneManager.h>
#include <engine/game/scene.h>
#include "MainScene.h"
#include <stdlib.h> 

using namespace vg;
using namespace vg::graphics;

void mainGame(Game* game)
{
	Game::log("test");
	MainScene *scene = new MainScene();
	game->getSceneManager()->addTemplateScene("scene", scene);

	game->getSceneManager()->changeScene("scene");

	//SHIP
	
}