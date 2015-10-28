
#include "engine/game/game.h"
#include "engine/game/SceneManager.h"
#include "engine/game/scene.h"

#include "scenes/MainScene.h"
#include "scenes/cameraScene.h"

using namespace vg;

void mainGame(Game* game)
{
	Game::log("test");
	MainScene *scene = new MainScene();
	//CameraScene* scene = new CameraScene();
	game->getSceneManager()->addTemplateScene("scene", scene);

	game->getSceneManager()->changeScene("scene");
}