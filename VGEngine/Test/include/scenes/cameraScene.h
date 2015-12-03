
#pragma once

#include "engine/game/scene.h"
#include "engine/utility/vec2f.h"

class CameraScene : public vg::Scene
{
public:
	CameraScene();
	~CameraScene();
	void loadObjects();

private:
	void createBorder(vg::Vec2f lt, vg::Vec2f rt);

};
