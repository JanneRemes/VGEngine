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
	glm::vec2 texCoords[4];

	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		auto *components = (*it)->getAllComponents();
		AnimationComponent *animation = nullptr;

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
			TransformComponent *transform = (*it)->getComponent<TransformComponent>();
			RenderComponent *render = (*it)->getComponent<RenderComponent>();
			Texture *texture = render->getTexture();
			
			float xOffset = render->getTexture()->getWidth() / animation->mFrameColumnCount;
			float yOffset = render->getTexture()->getHeight() / animation->mFrameRowCount;
			
			animation->mXOffSet = xOffset;
			animation->mYOffSet = yOffset;

			texCoords[0] = glm::vec2(xOffset * 0, yOffset * 1);
			texCoords[1] = glm::vec2(xOffset * 0, yOffset * 0);
			texCoords[2] = glm::vec2(xOffset * 1, yOffset * 0);
			texCoords[3] = glm::vec2(xOffset * 1, yOffset * 1);
			
			render->setTexCoords(texCoords);
			animation->isInitialized = true;
		}
		
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