#include "engine/game/transformComponent.h"
#include <stdlib.h> 
using namespace vg;

TransformComponent::TransformComponent() :Component()
{
	//mX = 0.0f;
	//mY = 0.0f;
	mPosition = Vector2<float>();
	mScale = 1.0f;
//	mRotation = 0;
}
TransformComponent::TransformComponent(float x, float y, float rotation) :Component()
{
	mPosition = Vector2<float>(x, y);
	mRotation = rotation;
}

TransformComponent::~TransformComponent()
{
}
