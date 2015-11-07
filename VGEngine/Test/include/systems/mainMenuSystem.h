
#include "engine/game/system.h"
#include "engine/game/scene.h"

class MainMenuSystem : public vg::System
{
public:
	MainMenuSystem(vg::Scene *scene);
	~MainMenuSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:
	vg::Scene* mScene;
};
