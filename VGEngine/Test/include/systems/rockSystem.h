#pragma once
#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/game/scene.h"
#include "engine/utility/timer.h"

using namespace vg;
class rockSystem :
	public System
{ 
public:
	rockSystem(Scene *scene);
	~rockSystem();
	void update(std::vector<vg::GameObject*> *gameObjects,float deltaTime);
	
private:
	Scene *scene;
	GameObject *rock;
	GameObject *bar1;
	GameObject *bar2;
};

