
#pragma once

#include <vector>
#include <engine/game/system.h>
#include <engine/game/gameObject.h>
#include <engine/game/game.h>
#include <engine/utility/timer.h>
#include <engine/game/scene.h>
#include <engine/utility/Vector2.h>

class TestSystem : public vg::System
{
public:
	TestSystem(vg::Scene *scene);
	~TestSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
private:
	vg::Scene *scene;
	vg::Vector2<int> dogeDir;
	int camDir;
	float camRotDir;
	float camZoom;
	int camState;
};