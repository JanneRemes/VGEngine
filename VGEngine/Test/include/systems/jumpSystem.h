#pragma once

#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/utility/timer.h"
#include "engine/game/scene.h"
#include "engine/game/physicsSystem.h"
#include "engine\game\physicsJoint.h"
#include "engine/utility/vec2f.h"

#include <vector>
#define SLOMO_TIME_STEP 0.0011f
#define DEFAULT_TIME_STEP 0.016666f
#define SLOMO_TIME 4.0f
#define SLOMO_TIME_STEP_INCREASE 0.001f;
void doge(vg::GameObject *other);
class JumpSystem : public vg::System
{

public:
	enum SLOMO_STATE
	{
		NO_SLOMO,
		SLOMO,
		SLOMO_ENDING,
		SLOMO_MUSIC_STARTED,
		SLOMO_DONE
	};
	JumpSystem(vg::Scene *scene);
	~JumpSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
	void onHit(vg::GameObject *other, vg::GameObject *other2);
	void reset();
	void tiltLeft();
	void tiltRight();
	void prepareLaunch();
	void Launch();
private:
	float slomo_acceleration;
	void backgroundUpdate(std::vector<vg::GameObject*> *gameObjects);
	vg::Timer slomoTimer;
	SLOMO_STATE slomo_state;
	vg::Scene *scene;
	vg::PhysicsSystem *system;
	vg::GameObject *snowboard;
	vg::GameObject *muumiObject;
	vg::Joint *muumiJoint;
	vg::GameObject* textObject;
	vg::GameObject* powerTextObject;
	vg::GameObject *background;
	vg::GameObject *landingZone;

	// Landing zone
	std::vector<vg::Vec2f> listOfCustomPoints;

	float jumpDistance;
	float jumpPosition;
	int launchPower;
	bool launched;
};