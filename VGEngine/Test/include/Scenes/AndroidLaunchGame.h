#pragma once
#include "engine\game\scene.h"
#include "engine\game\gameObject.h"
#include "systems\androidLaunchSystem.h"

class AndroidLaunchGame :
	public vg::Scene
{
public:
	AndroidLaunchGame();
	~AndroidLaunchGame();
	void loadObjects();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:

	vg::GameObject *android;
};