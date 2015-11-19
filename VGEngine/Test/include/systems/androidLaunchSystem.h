#pragma once
#include "engine\game\system.h"
#include "engine\game.h"
#include "engine\game\PhysicsComponent.h"
#include "engine\game\physicsSystem.h"
#include "engine\game\scene.h"
#include "Scenes\AndroidLaunchGame.h"

enum BarState { INCREASING, DECREASING };
enum Background {BACKGROUND1, BACKGROUND2, RESET};

class AndroidLaunchSystem : public vg::System
{
public:
	AndroidLaunchSystem(vg::Scene *scene);
	~AndroidLaunchSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
	void backgroundUpdate();
	vg::Vec2f normalize(vg::Vec2f vec2);

private:

	enum BarState bState;
	enum Background bgState;
	float barYIncrement;
	bool clickInit;
	bool isShot;
	float speed;
	double distance;
	glm::vec2 barTexCoords[4];
	vg::Vec2f ballPos;
	vg::Vec2f clickPos;
	vg::Vec2f normalizedVec;
	vg::Vec2f defaultPos;
	vg::GameObject *android;
	vg::GameObject *powerBar;
	vg::GameObject *background1;
	vg::GameObject *background2;
	vg::GameObject *textObject;
	vg::Scene *scene;
	vg::PhysicsSystem *physicSystem;
};