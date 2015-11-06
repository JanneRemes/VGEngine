#pragma once
#include "engine\game\system.h"
#include "engine\game\physicsCircleComponent.h"
#include "engine\game\physicsSystem.h"
#include "engine\game\scene.h"
#include "Scenes\AndroidLaunchGame.h"

class AndroidLaunchSystem : public vg::System
{
public:
	AndroidLaunchSystem(vg::Scene *scene);
	~AndroidLaunchSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:

	vg::GameObject *android;
	vg::Scene *scene;
	vg::PhysicsSystem *physicSystem;
};