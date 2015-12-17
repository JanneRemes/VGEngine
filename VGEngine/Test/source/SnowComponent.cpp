#include "SnowComponent.h"


SnowComponent::SnowComponent(vg::Vec2f startPos, vg::Vec2f velocity)
{
	this->startPos = startPos;
	this->velocity = velocity;
}


SnowComponent::~SnowComponent()
{
}
