
#pragma once

#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/utility/timer.h"
#include "engine/game/scene.h"
#include "engine/game/physicsSystem.h"
#include "engine/utility/Vector2.h"

#include <vector>

class PhysicsTestSystem : public vg::System
{
public:
	PhysicsTestSystem(vg::Scene *scene);
	~PhysicsTestSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
	void createPapis(vg::Vector2<float> pos);
private:
	vg::Scene *scene;
	vg::PhysicsSystem *system;
	vg::GameObject *physicsTest;
	vg::GameObject *physicsTest3;
	vg::GameObject *animationTest;
	vg::Timer newPositionTime;
	vg::Vector2<float> randPos;
};