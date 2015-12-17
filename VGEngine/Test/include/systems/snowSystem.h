#pragma once
#include "engine/game/system.h"

#include "engine/game/gameObject.h"
#include "engine\game\transformComponent.h"
#include "engine/game/scene.h"
#include "engine/utility/timer.h"
#include "engine/game/physicsSystem.h"

using namespace vg;
class snowSystem :
	public System
{ 
public:
	snowSystem(Scene *scene);
	~snowSystem();
	void update(std::vector<vg::GameObject*> *gameObjects,float deltaTime);

private:
	PhysicsSystem *system;
	Scene *scene;

};