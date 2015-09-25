
#include "engine/game/transformComponent.h"
#include <stdlib.h> 
#include "engine/game/gameObject.h"
#include <math.h>  
#include "engine/utility/math.h"
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
	if ( mGameObject != nullptr )
	{
		if (mGameObject->getParent() == nullptr)
		{
			return mPosition;
		}
		else
		{
			TransformComponent *transformComponent = mGameObject->getParent()->getComponent<TransformComponent>();
			if (transformComponent != nullptr)
			{
				vg::Vector2<int> parentPos = transformComponent->getLocalPosition();
				vg::Vector2<int> parentOrigo = transformComponent->getOrigin();
				vg::Vector2<int> tempPos = parentPos + parentOrigo + getLocalPosition();

				return tempPos;
			}
		}
	}
	

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

vg::Vector2<int> TransformComponent::getSize()
{
    return mSize;
}



void TransformComponent::setSize(const vg::Vector2<int> size)
{
    mSize = size;
}

float TransformComponent::getRotation()
{
    return mRotation;
}
//TODO fix

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
		Log("vgengine", "setLayer value cannot be higher than 10000 (transformcomponent)!","");
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