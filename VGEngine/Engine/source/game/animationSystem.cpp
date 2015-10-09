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

void AnimationSystem::initAnimations(GameObject *gameObject)
{
	glm::vec2 texCoords[4];

	auto *components = gameObject->getAllComponents();
	AnimationComponent *animation = nullptr;
	RenderComponent *render = nullptr;

	for (std::unordered_map<const std::type_info*, Component*>::iterator ij = components->begin(); ij != components->end(); ij++)
	{		
		if (dynamic_cast<AnimationComponent*>(ij->second) != nullptr)
		{
			animation = dynamic_cast<AnimationComponent*>(ij->second);
			break;
		}
	}
	
	for (std::unordered_map<const std::type_info*, Component*>::iterator ij = components->begin(); ij != components->end(); ij++)
	{
		if (dynamic_cast<RenderComponent*>(ij->second) != nullptr)
		{
			render = dynamic_cast<RenderComponent*>(ij->second);
			break;
		}
	}
	if (animation != nullptr)
	{
			//--
		float xOffset = 1.0f / animation->mFrameColumnCount;
		float yOffset = 1.0f / animation->mFrameRowCount;
			//---
		animation->mXOffSet = xOffset;
		animation->mYOffSet = yOffset;
		animation->mXOffSetIndex = 0;
		animation->mYOffSetIndex = 0;

		texCoords[0] = glm::vec2(0, yOffset);
		texCoords[1] = glm::vec2(0, 0);
		texCoords[2] = glm::vec2(xOffset, 0);
		texCoords[3] = glm::vec2(xOffset, yOffset);
			//--
		render->setTexCoords(texCoords);
		//--
		animation->isInitialized = true;
		//--
	}
		
}
void AnimationSystem::update(std::vector<GameObject*> *gameObjects, float deltaTime)
{	
	glm::vec2 texCoords[4];
	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		auto *components = (*it)->getAllComponents();
		AnimationComponent *animation = nullptr;
		RenderComponent *render = nullptr;
			
		for (std::unordered_map<const std::type_info*, Component*>::iterator ij = components->begin(); ij != components->end(); ij++)
		{
			if (dynamic_cast<AnimationComponent*>(ij->second) != nullptr)
			{
				animation = dynamic_cast<AnimationComponent*>(ij->second);
				break;
			}
		}
		if (animation != nullptr)
		{
			animation->mAnimationTimer += deltaTime;

			if (animation->isInitialized == false)
			{
				initAnimations((*it));
			}
			
			else if (animation->mAnimationTimer >= animation->mAnimationInterval)
			{
				RenderComponent *render = (*it)->getComponent<RenderComponent>();

				animation->mXOffSetIndex++;
				animation->mFrameIndex++;

				if (animation->mFrameIndex > animation->mFrameTotalCount)
				{
					animation->mFrameIndex = 0;
					animation->mYOffSetIndex = 0;
					animation->mXOffSetIndex = 0;
				}

				else if (animation->mXOffSetIndex > animation->mFrameColumnCount)
				{
					animation->mXOffSetIndex = 0;
					animation->mYOffSetIndex++;
				}

				else
				{
					animation->mXOffSetIndex++;
				}

				texCoords[0] = glm::vec2(animation->mXOffSet * animation->mXOffSetIndex, animation->mYOffSet * (animation->mYOffSetIndex + 1));
				texCoords[1] = glm::vec2(animation->mXOffSet * animation->mXOffSetIndex, animation->mYOffSet * animation->mYOffSetIndex);
				texCoords[2] = glm::vec2(animation->mXOffSet * (animation->mXOffSetIndex + 1), animation->mYOffSet * animation->mYOffSetIndex);
				texCoords[3] = glm::vec2(animation->mXOffSet * (animation->mXOffSetIndex + 1), animation->mYOffSet * (animation->mYOffSetIndex + 1));

				render->setTexCoords(texCoords);
			}
			
		}
	}
}