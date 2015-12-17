#pragma once
#include "engine\game\component.h"
#include "engine/utility/vec2f.h"
class SnowComponent :
	public vg::Component
{
	friend class snowSystem;
public:
	SnowComponent(vg::Vec2f startPos, vg::Vec2f velocity);
	~SnowComponent();
private:
	vg::Vec2f startPos;
	vg::Vec2f velocity;
};

