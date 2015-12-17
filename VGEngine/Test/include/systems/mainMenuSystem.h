
#include "engine/game/system.h"
#include "engine/game/scene.h"
#include "engine/utility/vec2f.h"
#include "engine/utility/timer.h"
// forward declaration
namespace vg
{
	class GameObject;
}

class MainMenuSystem : public vg::System
{
public:
	MainMenuSystem(vg::Scene *scene);
	~MainMenuSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:
	bool updateButton(vg::GameObject* obj);
	vg::Timer lightSpawnTimer;
	float lightDelay;
	int lightMaxCount;
	int lightSpawnAtOnce;
	int currentLightCount;
	vg::Scene* mScene;
	std::vector<std::string> sceneNames;
	std::vector<std::string>::iterator selectedScene;
	vg::Vec2f inputDown;
	vg::Vec2f inputRelease;
};
