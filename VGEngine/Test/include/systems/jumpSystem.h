#pragma once

#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/utility/timer.h"
#include "engine/game/scene.h"
#include "engine/game/physicsSystem.h"
#include "engine\game\physicsJoint.h"
#include "engine/utility/vec2f.h"

#include <vector>
void doge(vg::GameObject *other);
class JumpSystem : public vg::System
{
public:
	JumpSystem(vg::Scene *scene);
	~JumpSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
	void onHit(vg::GameObject *other, vg::GameObject *other2);
	void reset();
private:
	vg::Scene *scene;
	vg::PhysicsSystem *system;
	vg::GameObject *snowboard;
	vg::GameObject *muumiObject;
	vg::Joint *muumiJoint;
	vg::GameObject* textObject;
	vg::GameObject* powerTextObject;
	vg::GameObject *background;
	vg::GameObject *landingZone;


	float jumpDistance;
	float jumpPosition;
	int launchPower;
	bool launched;
};