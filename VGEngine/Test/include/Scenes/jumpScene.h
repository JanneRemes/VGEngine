#pragma once

#include "engine\game\scene.h"

class JumpScene : public vg::Scene
{
public:
	JumpScene();
	~JumpScene();
	void loadObjects();

private:
	int hillSizeModifier;
	float lowestPoint;
};
