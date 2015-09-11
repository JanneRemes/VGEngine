
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
		void update(std::vector<GameObject*> *gameObjects,float deltaTime);

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

		/**
		Set camera position
		@param x position in pixels
		@param y position in pixels
		*/
		void setCameraPosition(float x, float y);

		/**
		Move camera position
		@param x position in pixels
		@param y position in pixels
		*/
		void moveCameraPosition(float x, float y);

		/**
		Set camera rotation
		@param rotation in degrees
		*/
		void setCameraRotation(float rotation);

		/**
		Rotate camera position
		@param rotation in degrees
		*/
		void rotateCamera(float rotation);

		/**
		Set camera scale
		@param scaleX must be greater than zero
		@param scaleY must be greater than zero
		*/
		void setCameraScale(float scaleX, float scaleY);

		/**
		Set camera scale
		@param scaleX must be greater than zero
		@param scaleY must be greater than zero
		*/
		void scaleCamera(float scaleX, float scaleY);

	private:
		/**
		Sends new uniform values to shader
		*/
		void updateShader(graphics::Shader* shader, TransformComponent* transform);

		glm::vec2 mCameraPosition;	///Camera position in pixels
		float mCameraRotation;		///Camera rotation in degrees
		glm::vec2 mCameraScale;		///Camera scale, must be greater than zero
	};

}