#pragma once
#include <vector>
#include <engine/game/system.h>
#include <engine/game/gameObject.h>
#include <engine/game/game.h>
#include <engine/utility/timer.h>
#include <engine/game/scene.h>

class sceneChangeSystem : public vg::System
{
public:
	sceneChangeSystem(vg::Scene *scene);
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
private:
	vg::Scene *scene;
};