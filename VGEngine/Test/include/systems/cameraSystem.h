
#pragma once

#include "engine/game/system.h"
#include "engine/utility/timer.h"

class CameraSystem : public vg::System
{
public:
	CameraSystem();
	~CameraSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:
	float cameraSpeed;
	vg::Timer timer;
};