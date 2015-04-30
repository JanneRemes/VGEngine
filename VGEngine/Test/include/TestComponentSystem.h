#pragma once
#include "engine/game/system.h"
#include "engine/game/gameObject.h"
class TestComponentSystem:
	public vg::System
{
public:
	TestComponentSystem();
	~TestComponentSystem();
	void update(std::vector<vg::GameObject*> *gameObjects);
};

