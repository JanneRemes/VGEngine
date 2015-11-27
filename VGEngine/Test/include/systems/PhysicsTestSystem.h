
#pragma once

#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/utility/timer.h"
#include "engine/game/scene.h"
#include "engine/game/physicsSystem.h"
#include "engine\game\physicsJoint.h"
#include "engine/utility/vec2f.h"

#include <vector>

class PhysicsTestSystem : public vg::System
{
public:
	PhysicsTestSystem(vg::Scene *scene);
	~PhysicsTestSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
	void onHit(vg::GameObject *other, vg::GameObject *other2);
	void createPapis(vg::Vec2f pos);
private:
	vg::Scene *scene;
	vg::PhysicsSystem *system;
	vg::GameObject *physicsTest;
	vg::GameObject *physicsTest3;
	vg::GameObject *animationTest;
	vg::Timer newPositionTime;
	vg::Vec2f randPos;
};