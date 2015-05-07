
#include "engine/game/renderSystem.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/game/game.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/game/triangleComponent.h"
#include "engine/game/transformComponent.h"
#include "engine/graphics/opengl.h"

#include <vector>
#include <typeinfo>

using namespace vg;
using namespace vg::graphics;

RenderSystem::RenderSystem() :System()
{

}


RenderSystem::~RenderSystem()
{

}
void RenderSystem::update(std::vector<GameObject*> *gameObjects)
{
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		RenderComponent* component = nullptr;
		auto *components = (*it)->getAllComponents();

		for (std::unordered_map<const std::type_info*, Component*>::iterator ij = components->begin(); ij != components->end(); ij++)
		{
			//component = dynamic_cast<RenderComponent*>(components[i]);
			if (typeid((RenderComponent*)ij->second) == typeid(RenderComponent*))
			{
				component = dynamic_cast<RenderComponent*>(ij->second);
				break;
			}
		}

		//TriangleComponent* component = gameObject->GetComponent<TriangleComponent>();
		TransformComponent* transformComponent = (*it)->GetComponent<TransformComponent>();
		if (component != nullptr)
		{
			vg::graphics::VertexBuffer vBuffer(*component->getVertices());
			IndexBuffer iBuffer(*component->getIndices());
			Shader *shader = Game::getInstance()->getGraphics()->getShader();
			Texture* texture = component->getTexture();

			if (texture != nullptr)
			{
				if (texture->isLoaded())
				{
					shader->useProgram();
					texture->bind();
					shader->unUseProgram();
				}
			}

			if (transformComponent == nullptr)
				GraphicsDevice::draw(shader, &vBuffer, &iBuffer);
			else
			{
				shader->setPosition(transformComponent->getPosition() - transformComponent->getOrigin());
				shader->setSize(transformComponent->getSize());
				shader->setRotation(transformComponent->getRotation());
				shader->setLayer(transformComponent->getLayer());
				
				GraphicsDevice::draw(shader, &vBuffer, &iBuffer);
			}
			
			if (texture != nullptr)
			{
				if (texture->isLoaded())
				{
					shader->useProgram();
					texture->unbind();
					shader->unUseProgram();
				}
			}
		}
	}
}