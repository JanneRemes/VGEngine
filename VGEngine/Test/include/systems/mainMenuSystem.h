
#include "engine/game/system.h"
#include "engine/game/scene.h"

// forward declaration
namespace vg
{
	class QuadrangleComponent;
}

class MainMenuSystem : public vg::System
{
public:
	MainMenuSystem(vg::Scene *scene);
	~MainMenuSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:
	void setGreen(vg::QuadrangleComponent* quad);
	void setBlue(vg::QuadrangleComponent* quad);

	vg::Scene* mScene;
	std::vector<std::string> sceneNames;
	std::vector<std::string>::iterator selectedScene;
};
