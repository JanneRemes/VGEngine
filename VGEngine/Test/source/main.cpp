
#include "engine/game/game.h"
#include "engine/game/SceneManager.h"
#include "engine/game/scene.h"
#include "engine/game/physicsSystem.h"
#include "engine/graphics/font.h"

#include "scenes/MainScene.h"
#include "scenes/cameraScene.h"
#include "scenes/pappaScene.h"
#include "scenes\AndroidLaunchGame.h"
#include "scenes\rockThrowScene.h"
#include "scenes\jumpScene.h"
#include "engine/game/renderComponent.h"
#include "scenes/DogeScene.h"
#include "scenes/HighScoreScene.h"
using namespace vg;

void mainGame(Game* game)
{
	Game::log("test");

	// preloading large assets
	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();

	assetManager->load<sound::Sound>("muumitechno.mp3");

	assetManager->load<sound::Sound>("christmasremix.mp3");
	assetManager->load<sound::Sound>("Muumimusiikkia 39.mp3");

	//TODO clean up
	RenderComponent("papparunSmall2.png");
	RenderComponent("muumiBG.png");

	MainScene *scene = new MainScene();
	game->getSceneManager()->addTemplateScene("scene", scene);


	CameraScene* cameraScene = new CameraScene();
	game->getSceneManager()->addTemplateScene("cameraScene", cameraScene);

	PappaScene* pappaScene = new PappaScene();
	game->getSceneManager()->addTemplateScene("pappaScene", pappaScene);

	AndroidLaunchGame* androidScene = new AndroidLaunchGame();
	game->getSceneManager()->addTemplateScene("Android", androidScene);

	rockThrowScene* rockthrowScene = new rockThrowScene();
	game->getSceneManager()->addTemplateScene("rockThrowScene", rockthrowScene);

	JumpScene* jumpScene = new JumpScene();
	game->getSceneManager()->addTemplateScene("jumpScene", jumpScene);

	DogeScene* doge = new DogeScene();
	game->getSceneManager()->addTemplateScene("doge", doge);

	HighScoreScene* highscoreScene = new HighScoreScene();
	game->getSceneManager()->addTemplateScene("highscorescene", highscoreScene);

	game->getSceneManager()->changeScene("scene");
	
}