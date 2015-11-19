#pragma once
#include "engine\game\system.h"
#include "engine\game.h"
#include "engine\game\physicsCircleComponent.h"
#include "engine\game\physicsSystem.h"
#include "engine\game\scene.h"
#include "Scenes\AndroidLaunchGame.h"

enum BarState { INCREASING, DECREASING };

class AndroidLaunchSystem : public vg::System
{
public:
	AndroidLaunchSystem(vg::Scene *scene);
	~AndroidLaunchSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);
	vg::Vec2f normalize(vg::Vec2f vec2);

private:

	enum BarState bState;
	float barYIncrement;
	bool mouseIsDown;
	bool isShot;
	float speed;
	glm::vec2 barTexCoords[4];
	vg::Vec2f ballPos;
	vg::Vec2f clickPos;
	vg::Vec2f normalizedVec;
	vg::Vec2f defaultPos;
	vg::GameObject *android;
	vg::GameObject *powerBar;
	vg::Scene *scene;
	vg::PhysicsSystem *physicSystem;
};