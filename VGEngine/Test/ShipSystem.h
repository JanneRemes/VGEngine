#pragma once
#include "engine/game/system.h"
#include "engine/game/gameObject.h"
#include "engine/game/scene.h"
//#include "engine/game/scene.h"
//

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
	Game *mGame;
	
};

