#pragma once
#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/game/scene.h"
#include "engine/utility/timer.h"

using namespace vg;
class ShipSystem :
	public System
{ 
public:
	ShipSystem();
	~ShipSystem();
	void update(std::vector<vg::GameObject*> *gameObjects,float deltaTime);
	Scene *mScene;
private:
	GameObject *mBullet;
    vg::Timer mCoolDownTimer;
    float mCoolDown;
};

