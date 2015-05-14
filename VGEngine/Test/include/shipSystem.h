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
	ShipSystem(Game* game);
	~ShipSystem();
	void update(std::vector<vg::GameObject*> *gameObjects);
	Scene *mScene;
private:
	GameObject *whyudodis;
	Game *mGame;
    vg::Timer mCoolDownTimer;
    float mCoolDown;
};

