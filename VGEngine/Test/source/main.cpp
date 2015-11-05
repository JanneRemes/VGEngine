
#include "engine/game/game.h"
#include "engine/game/SceneManager.h"
#include "engine/game/scene.h"

#include "scenes/MainScene.h"
#include "scenes/cameraScene.h"
#include "scenes/pappaScene.h"

#include "engine/game/physicsSystem.h"
using namespace vg;

void mainGame(Game* game)
{
	Game::log("test");

	MainScene *scene = new MainScene();
	game->getSceneManager()->addTemplateScene("scene", scene);
	game->getSceneManager()->changeScene("scene");

	CameraScene* cameraScene = new CameraScene();
	game->getSceneManager()->addTemplateScene("cameraScene", cameraScene);

	PappaScene* pappaScene = new PappaScene();
	game->getSceneManager()->addTemplateScene("pappaScene", pappaScene);

}