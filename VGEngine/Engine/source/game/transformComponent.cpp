#include "engine/game/transformComponent.h"
#include <stdlib.h> 
using namespace vg;

TransformComponent::TransformComponent()
{
	//mX = 0.0f;
	//mY = 0.0f;
	mPosition = Vector2<float>();
}
TransformComponent::TransformComponent(float x, float y, float rotation)
{
	mPosition = Vector2<float>(x, y);
	mRotation = rotation;
}

TransformComponent::~TransformComponent()
{
}
void TransformComponent::update()
{
}