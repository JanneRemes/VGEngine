#pragma once
#include "engine\game\system.h"
#include "engine\game\animationComponent.h"

namespace vg
{
	/*
		System for animating sprites
	*/
	class AnimationSystem : 
		public System
	{
	public:
		AnimationSystem();
		~AnimationSystem();

		void initAnimations(std::vector<GameObject*> *gameObjects);
		void update(std::vector<GameObject*> *gameObjects, float deltaTime);

	};
}