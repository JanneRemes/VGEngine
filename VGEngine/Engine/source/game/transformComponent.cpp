
#include "engine/game/transformComponent.h"
#include <stdlib.h> 
#include "engine/game/gameObject.h"
using namespace vg;
uint TransformComponent::mCurrentLayer = 0;
TransformComponent::TransformComponent(): Component()
{
    mPosition = Vector2<int>(0, 0);
    mSize = Vector2<int>(0, 0);
    mRotation = 0.0f;
    mLayer = 0u;
    mOrigin = Vector2<int>(0, 0);
}

TransformComponent::TransformComponent(const TransformComponent &transform)
{
	mPosition = transform.mPosition;
	mSize = transform.mSize;
	mRotation = transform.mRotation;
	mLayer = getDefaultLayer();
	mOrigin = transform.mOrigin;
}

TransformComponent::TransformComponent(vg::Vector2<int> position, vg::Vector2<int> size,
    float rotation, uint layer, vg::Vector2<int> origin)
    :Component(), mPosition(position), mSize(size), mRotation(rotation), mLayer(layer), mOrigin(origin)
{
}

TransformComponent::~TransformComponent()
{
}

vg::Vector2<int> TransformComponent::getLocalPosition()
{
    return mPosition;
}
//TODO fix
vg::Vector2<int> TransformComponent::getWorldPosition()
{
	/*if ( mGameObject != nullptr )
	{
		if (mGameObject->getParent() != nullptr)

		return mPosition;
	}*/
	/*
	TransformComponent *transformComponent = mGameObject->getComponent<TransformComponent>();
	if (transformComponent != nullptr)
	{
		vg::Vector2<int> parentPos = transformComponent->getLocalPosition();
		vg::Vector2<int> parentOrigo = transformComponent->getOrigin();
		vg::Vector2<int> tempPos = parentPos + parentOrigo + getLocalPosition() + getOrigin();
		return tempPos;
	}*/
	return mPosition;
}
void TransformComponent::setPosition(const Vector2<int> position)
{
    mPosition = position;
}

void TransformComponent::move(Vector2<int> change)
{
    mPosition += change;
}

vg::Vector2<int> TransformComponent::getLocalSize()
{
    return mSize;
}
//TODO fix
vg::Vector2<int> TransformComponent::getWorldSize()
{
	return mSize;
}


void TransformComponent::setSize(const vg::Vector2<int> size)
{
    mSize = size;
}

float TransformComponent::getLocalRotation()
{
    return mRotation;
}
//TODO fix
float TransformComponent::getWorldRotation()
{
	/*if (mGameObject->getParent() == nullptr)
	{
		return mRotation;
	}
	TransformComponent *transformComponent = mGameObject->getComponent<TransformComponent>();
	if (transformComponent != nullptr)
	{
		float parentPos = transformComponent->getLocalRotation();
		return parentPos + getLocalRotation();
	}*/
	return mRotation;
}

void TransformComponent::setRotation(float rotation)
{
    mRotation = rotation;
}

void TransformComponent::rotate(float rotation)
{
    setRotation(mRotation + rotation);
}

float TransformComponent::getLayer()
{
	return mLayer * 0.0001f;
}

void TransformComponent::setLayer(uint layer)
{
	if (layer > 10000)
	{
		Log("engine", "setLayer value cannot be higher than 10000 (transformcomponent)!","");
		layer = 10000;
	}
	mLayer = layer;
}

vg::Vector2<int> TransformComponent::getOrigin()
{
    return mOrigin;
}

void TransformComponent::setOrigin(const Vector2<int> origin)
{
    mOrigin = origin;
}
uint TransformComponent::getDefaultLayer()
{
	return mCurrentLayer++;
}