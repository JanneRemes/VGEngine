
#include "engine/game/system.h"
#include "engine/game/scene.h"
#include "engine/utility/vector2.h"

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

	vg::Scene* mScene;
	std::vector<std::string> sceneNames;
	std::vector<std::string>::iterator selectedScene;
	vg::Vector2<float> inputDown;
	vg::Vector2<float> inputRelease;
};
