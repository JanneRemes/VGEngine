
#pragma once

#include <engine/game/system.h>
#include <engine/game/game.h>
#include <engine/game/scene.h>

namespace vg
{
	class GameObject;
}

class DeleteSystem : public vg::System
{
public:
	DeleteSystem(vg::Game* game);
	~DeleteSystem();
	void update(std::vector<vg::GameObject*> *gameObjects);
	void setScene(vg::Scene* scene);

private:
	vg::Game* mGame;
	vg::Scene* mScene;
};