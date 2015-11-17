
#pragma once

#include "engine\game\scene.h"

class CameraScene : public vg::Scene
{
public:
	CameraScene();
	~CameraScene();
	void loadObjects();

private:
	void createBorder(float x, float y, float w, float h);

};
