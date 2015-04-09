#pragma once
#include "engine/game/componentSystem.h"
#include "engine/game/gameObject.h"
class TestComponentSystem:
	public vg::ComponentSystem
{
public:
	TestComponentSystem();
	~TestComponentSystem();
	void update(vg::GameObject* gameObject);
};

