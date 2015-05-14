
#pragma once

#include <vector>
#include <engine/game/system.h>
#include <engine/game/gameObject.h>
#include <engine/game/game.h>
#include <engine/utility/timer.h>
#include <engine/game/scene.h>

class EnemySystem : public vg::System
{
public:
	EnemySystem(vg::Game *game);
	~EnemySystem();
	void update(std::vector<vg::GameObject*> *gameObjects);
	void setScene(vg::Scene* scene);

private:
	vg::GameObject *mEnemyPrefab;
	vg::Game *mGame;
	vg::Scene *mScene;
	vg::Timer mSpawnTimer;
	float mSpawnDelay;
	int mEnemyCount;
	int mBulletCount;
};

