
#include "engine/game/renderSystem.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/graphics.h"
#include "engine/game/game.h"
#include "engine/graphics/vertexBuffer.h"
#include "engine/graphics/indexBuffer.h"
#include "engine/game/triangleComponent.h"
#include "engine/graphics/opengl.h"
#include "engine/game/renderComponent.h"
#include "engine/graphics/screen.h"
#include "engine/graphics/camera.h"

#include "../external/glm/gtc/matrix_transform.hpp"

#include <vector>
#include <typeinfo>

using namespace vg;
using namespace vg::graphics;
using namespace glm;

RenderSystem::RenderSystem() :System()
{
	mPriority = System::LAST;
}

void RenderSystem::update(std::vector<GameObject*> *gameObjects,float deltaTime)
{
	Shader* shader = Game::getInstance()->getGraphics()->getShader();
	shader->useProgram();
	shader->setUniform("unifNoTexture", false);

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
			mVertexBuffer.setData(*render->getVertices());
			mIndexBuffer.setData(*render->getIndices());
			
			Texture* texture = render->getTexture();
			if (texture != nullptr)
				texture->bind();
			else
				shader->setUniform("unifNoTexture", true);

			updateShader(shader, transform);
			Graphics::draw(shader, &mVertexBuffer, &mIndexBuffer);
			
			if (texture != nullptr)
				texture->unbind();
			else
				shader->setUniform("unifNoTexture", false);
		}
	}
	shader->setUniform("unifNoTexture", false);
	shader->unUseProgram();
}

void RenderSystem::updateProjection(Shader* shader, bool useCamera)
{
	vec2 screen(Screen::getX(), Screen::getY());
	vec2 camera(0, 0);
	float zoom = 0.0f;
	if (useCamera)
	{
		camera = vec2(Camera::getPosition().getX(), Camera::getPosition().getY());
		zoom = Camera::getZoom();
	}

	float left = camera.x + screen.x - screen.x * zoom;
	float right = camera.x + screen.x - screen.x * (1.0f - zoom);
	float bottom = camera.y + screen.y - screen.y * (1.0f - zoom);
	float top = camera.y + screen.y - screen.y * zoom;
	// left, right, bottom, top, near, far
	mat4 projection = ortho(left, right, bottom, top, -1000000.0f, 1000000.0f);
	
	if (useCamera)
	{
		Camera::mLeft = left;
		Camera::mTop = top;
		Camera::mRight = right;
		Camera::mBottom = bottom;

		//TODO: finish camera rotation
		/*
		projection = translate(projection, vec3(0.5f * screen.x, 0.5f * screen.y, 0.0f));
		projection = rotate(projection, Camera::getRotation(), vec3(0.0f, 0.0f, 1.0f));
		projection = translate(projection, vec3(-0.5f * screen.x, -0.5f * screen.y, 0.0f));
		*/
	}
	shader->setUniform("unifProjection", projection);
}

mat4 RenderSystem::modelTransform(Vector2<float> position, Vector2<float> origin, Vector2<float> size, float rotation)
{
	vec2 position2(position.getX() - origin.getX(), position.getY() - origin.getY());
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
	return modelTransform(transform->getWorldPosition(), transform->getOrigin(),
		transform->getSize(), transform->getWorldRotation());
}

void RenderSystem::updateShader(Shader* shader, TransformComponent* transform)
{
	updateProjection(shader, transform->getUsingCamera());
	if (transform != nullptr)
	{
		shader->setUniform("unifModel", modelTransform(transform));
		shader->setUniform("unifLayer", transform->getLayer());
	}
	else
	{
		shader->setUniform("unifModel", modelTransform(
			Vector2<float>(0, 0), Vector2<float>(0, 0), Vector2<float>(0, 0), 0.0f));
		shader->setUniform("unifLayer", 0.0f);
	}
	
}
