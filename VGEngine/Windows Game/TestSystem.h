
#pragma once

#include <vector>
#include <engine/game/system.h>
#include <engine/game/gameObject.h>
#include <engine/game/game.h>
#include <engine/utility/timer.h>
#include <engine/game/scene.h>

class TestSystem : public vg::System
{
public:
	TestSystem(vg::Scene *scene);
	~TestSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
private:
	vg::Scene *scene;
};