
#pragma once

#include "engine/game/system.h"

class CameraSystem : public vg::System
{
public:
	CameraSystem();
	~CameraSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:

};