#pragma once
#include "engine\game\system.h"
#include <engine/utility/vec2f.h>
class DogeSystem :
	public vg::System
{
public:
	DogeSystem();
	~DogeSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
private:
	int doges;
	bool isInputDown();
	vg::Vec2f getInputPos();
};

