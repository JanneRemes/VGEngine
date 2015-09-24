#include "engine\game\animationSystem.h"
#include "engine\game\renderComponent.h"
#include "engine\game\game.h"
#include "engine\graphics\graphics.h"
#include "engine\graphics\texture.h"

using namespace vg;
using namespace vg::graphics;

AnimationSystem::AnimationSystem()
{

}

AnimationSystem::~AnimationSystem()
{

}

void AnimationSystem::initAnimations(std::vector<GameObject*> *gameObjects)
{
	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		
	}
}
void AnimationSystem::update(std::vector<GameObject*> *gameObjects, float deltaTime)
{	
	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		AnimationComponent *animation = (*it)->getComponent<AnimationComponent>();
		RenderComponent *render = (*it)->getComponent<RenderComponent>();

		if (animation != nullptr && render != nullptr)
		{
			Texture* texture = render->getTexture();
			if (texture != nullptr)
			{

			}
		}
	}
}