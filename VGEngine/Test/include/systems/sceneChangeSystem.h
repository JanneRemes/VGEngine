
#pragma once

#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/utility/timer.h"
#include "engine/game/scene.h"
#include "engine/utility/Vector2.h"

#include <vector>

class sceneChangeSystem : public vg::System
{
public:
	sceneChangeSystem(vg::Scene *scene);
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:
	vg::Scene *scene;
	vg::Vector2<float> buttonPos;
	vg::Vector2<float> buttonSize;

};