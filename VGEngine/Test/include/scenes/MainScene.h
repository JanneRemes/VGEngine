
#pragma once

#include "engine/game/scene.h"
#include <string>

//forward declaration
namespace vg
{
	class GameObject;
}

class MainScene : public vg::Scene
{
public:
	MainScene();
	~MainScene();
	void loadObjects();

private:
	vg::GameObject* makeButton(std::string name, std::string texture, float y);

};

