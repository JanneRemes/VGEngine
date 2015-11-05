
#pragma once

#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/utility/timer.h"
#include "engine/game/scene.h"

#include <vector>

class EnemySystem : public vg::System
{
public:
	EnemySystem();
	~EnemySystem();
	void update(std::vector<vg::GameObject*> *gameObjects,float deltaTime);
	void setScene(vg::Scene* scene);

private:
	vg::GameObject *mEnemyPrefab;
	vg::Scene *mScene;
	vg::Timer mSpawnTimer;
	vg::Timer fpsTimer;
	float mSpawnDelay;
	int mEnemyCount;
	int mBulletCount;
};

