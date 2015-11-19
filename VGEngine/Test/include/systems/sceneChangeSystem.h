
#pragma once

#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/utility/timer.h"
#include "engine/game/scene.h"
#include "engine/utility/vec2f.h"

#include <vector>

class sceneChangeSystem : public vg::System
{
public:
	sceneChangeSystem(vg::Scene *scene);
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:
	vg::Scene *scene;
	int frameCount;
	float fpsTime;
};