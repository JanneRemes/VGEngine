#pragma once
#include "engine\game\scene.h"
class MainScene :
	public vg::Scene
{
public:
	MainScene();
	~MainScene();
	void loadObjects();
};

