#pragma once
#include "engine\game\system.h"
class DogeSystem :
	public vg::System
{
public:
	DogeSystem();
	~DogeSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
private:
	int doges;
};

