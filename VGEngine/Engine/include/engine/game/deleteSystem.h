
#pragma once

#include "engine/game/system.h"
#include "engine/game/scene.h"

namespace vg
{
	class GameObject;


	class DeleteSystem : public vg::System
	{
	public:
		DeleteSystem();
		~DeleteSystem();
		void update(std::vector<vg::GameObject*> *gameObjects,float deltaTime);
		void setScene(vg::Scene* scene);

	private:
		vg::Scene* mScene;
	};

}