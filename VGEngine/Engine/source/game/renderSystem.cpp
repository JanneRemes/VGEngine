
#include "engine/game/renderSystem.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/graphicsDevice.h"
#include "engine/game/game.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/game/triangleComponent.h"
#include "engine/graphics/opengl.h"

#include "../external/glm/gtc/matrix_transform.hpp"

#include <vector>
#include <typeinfo>

using namespace vg;
using namespace vg::graphics;
using namespace glm;

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
		RenderComponent* render = nullptr;
		auto *components = (*it)->getAllComponents();

		for (std::unordered_map<const std::type_info*, Component*>::iterator ij = components->begin(); ij != components->end(); ij++)
		{
			//component = dynamic_cast<RenderComponent*>(components[i]);
			if (typeid((RenderComponent*)ij->second) == typeid(RenderComponent*))
			{
				render = dynamic_cast<RenderComponent*>(ij->second);
				break;
			}
		}

		//TriangleComponent* component = gameObject->GetComponent<TriangleComponent>();
		TransformComponent* transform = (*it)->getComponent<TransformComponent>();
		if (render != nullptr)
		{
			vg::graphics::VertexBuffer vBuffer(*render->getVertices());
			IndexBuffer iBuffer(*render->getIndices());
			Shader* shader = Game::getInstance()->getGraphics()->getShader();
			Texture* texture = render->getTexture();

			shader->useProgram();
			if (texture != nullptr)
				texture->bind();

			updateShader(shader, transform);
			GraphicsDevice::draw(shader, &vBuffer, &iBuffer);
			
			if (texture != nullptr)
				texture->unbind();
			shader->unUseProgram();
		}
	}
}

void RenderSystem::updateShader(Shader* shader, TransformComponent* transform)
{
	if (transform != nullptr)
	{
		shader->setPosition(transform->getPosition() - transform->getOrigin());
		shader->setSize(transform->getSize());
		shader->setRotation(transform->getRotation());
		shader->setLayer(transform->getLayer());
		
		/*
		vec2 position((transform->getPosition() - transform->getOrigin()).getX(),
			(transform->getPosition() - transform->getOrigin()).getY());
		vec2 size(transform->getSize().getX(), transform->getSize().getY());
		
		mat4 modelTransform = mat4();
		modelTransform = translate(modelTransform, vec3(position, 0.0f));
		modelTransform = translate(modelTransform, vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		modelTransform = rotate(modelTransform, transform->getRotation(), vec3(0.0f, 0.0f, 1.0f));
		modelTransform = translate(modelTransform, vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		modelTransform = scale(modelTransform, vec3(size, 1.0f));

		shader->setUniform(UniformUsage::Model, modelTransform);
		shader->setUniform(UniformUsage::Layer, transform->getLayer());
		*/
	}
}