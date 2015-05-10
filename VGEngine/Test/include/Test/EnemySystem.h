#pragma once
//using namespace vg;
#include <vector>
#include <engine\game\system.h>
#include <engine\game\gameObject.h>
#include <engine\game\game.h>
#include <engine\utility\timer.h>
#include <engine\game\scene.h>
class EnemySystem
	:public vg::System
{
public:
	EnemySystem(vg::Game *game);
	~EnemySystem();
	void update(std::vector<vg::GameObject*> *gameObjects);
	vg::Scene *mScene;
private:
	vg::GameObject *mEnemyPrefab;
	vg::Game *mGame;
	vg::Timer mSpawnTimer;
	float mSpawnDelay;

};

