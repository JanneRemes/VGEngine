
#pragma once

#include "engine\game\system.h"
#include "engine\game\animationComponent.h"

namespace vg
{
	/*
		System for animating sprites
	*/
	class AnimationSystem : public System

	{
	public:
		AnimationSystem();
		~AnimationSystem();

		/**
		Updates render component to support animations
		@param gameObject to be modified
		*/
		void initAnimations(GameObject *gameObject);

		/**
		Updates AnimationComponents
		@param gameObjects to be updated
		@param deltaTime time the last update took
		*/
		void update(std::vector<GameObject*> *gameObjects, float deltaTime);

	};
}