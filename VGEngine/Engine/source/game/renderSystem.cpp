
#include "engine/game/renderSystem.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/graphics.h"
#include "engine/game/game.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/game/triangleComponent.h"
#include "engine/graphics/opengl.h"
#include "engine/game/renderComponent.h"

#include "../external/glm/gtc/matrix_transform.hpp"

#include <vector>
#include <typeinfo>

using namespace vg;
using namespace vg::graphics;
using namespace glm;

RenderSystem::RenderSystem() :System()
{
	updateProjection();
}

void RenderSystem::update(std::vector<GameObject*> *gameObjects,float deltaTime)
{
	Shader* shader = Game::getInstance()->getGraphics()->getShader();
	shader->useProgram();

	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		RenderComponent* render = nullptr;
		auto *components = (*it)->getAllComponents();
		for (std::unordered_map<const std::type_info*, Component*>::iterator ij = components->begin(); ij != components->end(); ij++)
		{
			if (dynamic_cast<RenderComponent*>(ij->second) != nullptr)
			{		
				render = dynamic_cast<RenderComponent*>(ij->second);
				break;
			}
		}

		TransformComponent* transform = (*it)->getComponent<TransformComponent>();
		if (render != nullptr)
		{
			vg::graphics::VertexBuffer vBuffer(*render->getVertices());
			IndexBuffer iBuffer(*render->getIndices());
			
			Texture* texture = render->getTexture();
			if (texture != nullptr)
				texture->bind();

			updateShader(shader, transform);
			Graphics::draw(shader, &vBuffer, &iBuffer);
			
			if (texture != nullptr)
				texture->unbind();
		}
	}
	shader->unUseProgram();
}

void RenderSystem::updateProjection()
{
	Shader* shader = Game::getInstance()->getGraphics()->getShader();
	shader->useProgram();
	vec2 screenSize(Game::getInstance()->getGraphics()->getContext()->getWidth(),
		Game::getInstance()->getGraphics()->getContext()->getHeight());
	mat4 projectionTransform = ortho(0.0f, screenSize.x, screenSize.y, 0.0f, -1.0f, 1.0f);
	shader->setUniform("unifProjection", projectionTransform);
	shader->unUseProgram();
}

mat4 RenderSystem::modelTransform(Vector2<int> position, Vector2<int> size, float rotation)
{
	vec2 position2(position.getX(), position.getY());
	vec2 size2(size.getX(), size.getY());

	mat4 model = mat4();
	model = translate(model, vec3(position2, 0.0f));
	model = translate(model, vec3(0.5f * size2.x, 0.5f * size2.y, 0.0f));
	model = rotate(model, rotation, vec3(0.0f, 0.0f, 1.0f));
	model = translate(model, vec3(-0.5f * size2.x, -0.5f * size2.y, 0.0f));
	model = scale(model, vec3(size2, 1.0f));
	return model;
}

mat4 RenderSystem::modelTransform(TransformComponent* transform)
{
	return modelTransform(transform->getWorldPosition() - transform->getOrigin(),
		transform->getSize(), transform->getWorldRotation());
}

void RenderSystem::setCameraPosition(float x, float y)
{
	mCameraPosition = vec2(x, y);
}

void RenderSystem::moveCameraPosition(float x, float y)
{
	mCameraPosition += vec2(x, y);
}

void RenderSystem::setCameraRotation(float rotation)
{
	mCameraRotation = rotation;
}

void RenderSystem::rotateCamera(float rotation)
{
	mCameraRotation += rotation;
}

void RenderSystem::setCameraScale(float scaleX, float scaleY)
{
	if (scaleX < 0)
		scaleX = 0;
	if (scaleY < 0)
		scaleY = 0;

	mCameraScale = vec2(scaleX, scaleY);
}

void RenderSystem::scaleCamera(float scaleX, float scaleY)
{
	setCameraScale(mCameraScale.x + scaleX, mCameraScale.y + scaleY);
}

void RenderSystem::updateShader(Shader* shader, TransformComponent* transform)
{
	if (transform != nullptr)
	{
		shader->setUniform("unifModel", modelTransform(transform));
		shader->setUniform("unifLayer", transform->getLayer());
	}
	else
	{
		shader->setUniform("unifModel", modelTransform(
			Vector2<int>(0, 0), Vector2<int>(0, 0), 0.0f));
		shader->setUniform("unifLayer", 0.0f);
	}
	
}
