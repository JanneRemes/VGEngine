
#pragma once

#include "engine\game\scene.h"

//forward declaration
namespace vg
{
	class TransformComponent;
}

class CameraScene : public vg::Scene
{
public:
	CameraScene();
	~CameraScene();
	void loadObjects();

private:
	void createBorder(vg::TransformComponent* transform);

};
