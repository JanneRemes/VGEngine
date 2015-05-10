
#pragma once

#include "engine/game/system.h"
#include "engine/graphics/shader.h"
#include "engine/game/transformComponent.h"
#include "engine/graphics/shader.h"

namespace vg
{
	/**
	System that draws GameObjects with RenderComponents
	*/
	class RenderSystem :public System
	{
	public:
		/**
		Initializes RenderSystem
		*/
		RenderSystem();

		/**
		Draws all the GameObjects that contain a RenderComponent.
		*/
		void update(std::vector<GameObject*> *gameObjects);

		/**
		Gets screen size from Game and sends new projection matrix to shader.
		*/
		void updateProjection();

		/**
		Makes a model transform matrix 
		*/
		static glm::mat4 modelTransform(Vector2<int> position, Vector2<int> size, float rotation);
		
		/**
		Makes a model transform matrix using values from a TransformComponent
		*/
		static glm::mat4 modelTransform(TransformComponent* transform);

	private:
		/**
		Sends new uniform values to shader
		*/
		void updateShader(graphics::Shader* shader, TransformComponent* transform);

	};

}