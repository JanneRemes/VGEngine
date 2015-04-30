#pragma once
#include "engine/game/system.h"
#include "engine/game/gameObject.h"
//

using namespace vg;
class ShipSystem :
	public System
{ 
	class Scene;
public:
	ShipSystem();
	~ShipSystem();
	void update(std::vector<vg::GameObject*> *gameObjects);
private:
	GameObject *mBullet;

};

