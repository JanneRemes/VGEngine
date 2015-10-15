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

		void initAnimations(GameObject *gameObject);
		void update(std::vector<GameObject*> *gameObjects, float deltaTime);

	};
}