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
	vg::Vector2<float> normalize(vg::Vector2<float> vec2);

private:

	enum BarState bState;
	float barYIncrement;
	bool mouseIsDown;
	bool isShot;
	float speed;
	glm::vec2 barTexCoords[4];
	vg::Vector2<float> ballPos;
	vg::Vector2<float> clickPos;
	vg::Vector2<float> normalizedVec;
	vg::Vector2<float> defaultPos;
	vg::GameObject *android;
	vg::GameObject *powerBar;
	vg::Scene *scene;
	vg::PhysicsSystem *physicSystem;
};