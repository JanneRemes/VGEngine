
#pragma once

#include <vector>
#include <engine/game/system.h>
#include <engine/game/gameObject.h>
#include <engine/game/game.h>
#include <engine/utility/timer.h>
#include <engine/game/scene.h>
#include "engine/game/physicsSystem.h"

class PhysicsTestSystem : public vg::System
{
public:
	PhysicsTestSystem(vg::Scene *scene);
	~PhysicsTestSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
private:
	vg::Scene *scene;
	vg::PhysicsSystem *system;
	vg::GameObject *physicsTest;
};