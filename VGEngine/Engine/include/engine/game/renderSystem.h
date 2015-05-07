
#pragma once

#include "engine/game/system.h"
#include "engine/graphics/shader.h"
#include "engine/game/transformComponent.h"

namespace vg
{

	/**
	System that updates renderComponents
	*/
	class RenderSystem :
		public System
	{
	public:
		RenderSystem();
		~RenderSystem();
		void update(std::vector<GameObject*> *gameObjects);

	private:
		void updateShader(graphics::Shader* shader, TransformComponent* transform);
	};

}