#pragma once
#include "engine/game/system.h"

#include "engine/game/gameObject.h"
#include "engine\game\transformComponent.h"
#include "engine/game/scene.h"
#include "engine/utility/timer.h"
#include "engine/game/physicsSystem.h"

enum Background { BACKGROUND1, BACKGROUND2, RESET };

using namespace vg;
class rockSystem :
	public System
{ 
public:
	rockSystem(Scene *scene);
	~rockSystem();
	void update(std::vector<vg::GameObject*> *gameObjects,float deltaTime);
	void updateBars();
	void updateExplosives(int amount, std::vector<vg::GameObject*> *gameObjects);
	void updateInputs();
	void updateView();
	
private:
	PhysicsSystem *system;

	Scene *scene;

	GameObject *background1;
	GameObject *background2;

	GameObject *rock;

	GameObject *bar1;
	GameObject *bar2;

	GameObject *indicator1;
	GameObject *indicator2;

	GameObject *explosive;

	int height, minHeight, maxHeight;
	bool heightLock, goUp, goDown;

	int power, minPower, maxPower;
	bool powerLock, powerUp, powerDown;

	bool shot;
	int i;

	enum Background bgState;
	TransformComponent* currentBackground;

	Timer timer;
};

