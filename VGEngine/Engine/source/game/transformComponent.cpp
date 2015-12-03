
#include "engine/game/transformComponent.h"
#include "engine/game/gameObject.h"
#include "engine/utility/math.h"
#include "../external/glm/gtc/matrix_transform.hpp"

#include <math.h>  
#include <stdlib.h>

using namespace vg;

/// values used for tracking reserved layers
static unsigned int mCurrentLayers[] = { 1, 1000, 2000, 8000, 9000 };
static unsigned int mLayerMinValues[] = { 1, 1000, 2000, 8000, 9000 };
static unsigned int mLayerMaxValues[] = { 999, 1999, 7999, 8999, 10000 };

TransformComponent::TransformComponent(): Component()
{
    mPosition = Vec2f(0, 0);
	mSize = Vec2f(0, 0);
    mRotation = 0.0f;
    mLayer = 0u;
	mOrigin = Vec2f(0, 0);
}

TransformComponent::TransformComponent(const TransformComponent &transform)
{
	mPosition = transform.mPosition;
	mSize = transform.mSize;
	mRotation = transform.mRotation;
	mLayerGroup = transform.mLayerGroup;
	setLayer(mLayerGroup);
	mOrigin = transform.mOrigin;
	mUsingCamera = transform.mUsingCamera;
}

TransformComponent::TransformComponent(Vec2f position, LayerGroup layerGroup, bool useCamera)
	: mPosition(position), mSize(Vec2f(0, 0)), mRotation(0), mOrigin(Vec2f(0, 0)), mLayerGroup(layerGroup), mUsingCamera(useCamera)
{
	setLayer(mLayerGroup);
}

TransformComponent::TransformComponent(vg::Vec2f position, vg::Vec2f size,
	float rotation, vg::Vec2f origin, LayerGroup layerGroup, bool useCamera)
	:Component(), mPosition(position), mSize(size), mRotation(rotation), mOrigin(origin), mLayerGroup(layerGroup), mUsingCamera(useCamera)
{
	setLayer(layerGroup);
}

TransformComponent::TransformComponent(Vec2f leftTop, Vec2f rightBottom, Vec2f origin, LayerGroup layerGroup, bool useCamera)
	: mOrigin(origin), mRotation(0), mLayerGroup(layerGroup), mUsingCamera(useCamera)
{
	setLayer(mLayerGroup);
	mPosition = leftTop + mOrigin;
	mSize = Vec2f(rightBottom.x - leftTop.x, rightBottom.y - leftTop.y);
}

TransformComponent::TransformComponent(Vec2f leftTop, float height, Vec2f rightTop, LayerGroup layerGroup, bool useCamera)
	:mLayerGroup(layerGroup), mUsingCamera(useCamera)
{
	float distance = leftTop.distance(rightTop);
	mSize = Vec2f(distance, height);
	Vec2f origin = mSize;
	origin *= 0.5f;
	mRotation = Vec2f::angle(leftTop, rightTop);
	distance *= 0.5f;
	mPosition = leftTop + Vec2f(cos(Math::degreesToRadians(mRotation)) * distance, 
		sin(Math::degreesToRadians(mRotation)) * distance);
	mOrigin = origin;
	setLayer(mLayerGroup);
}

TransformComponent::~TransformComponent()
{
}

vg::Vec2f TransformComponent::getLocalPosition()
{
    return mPosition;
}

//TODO fix
vg::Vec2f TransformComponent::getWorldPosition()
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
				vg::Vec2f parentPos = transformComponent->getLocalPosition();
				vg::Vec2f parentOrigo = transformComponent->getOrigin();
				vg::Vec2f tempPos = parentPos + parentOrigo /*+ getLocalPosition()*/;
			
				float rotation = transformComponent->getLocalRotation();

				vg::Vec2f vector = getLocalPosition() -tempPos;
				glm::mat4 transu;
				transu = glm::rotate(transu, glm::radians(rotation), glm::vec3(0, 0, 1.0f));
				glm::vec4 result = transu * glm::vec4(vector.x, vector.y, 0.0f, 1.0f);
				vg::Vec2f syopa = vg::Vec2f(result.x, result.y);

				return tempPos;
			}
		}
	}
	

	return mPosition;
}

void TransformComponent::setPosition(const Vec2f position)
{
    mPosition = position;
}

void TransformComponent::setX(float x)
{
	mPosition.x = x;
}

void TransformComponent::setY(float y)
{
	mPosition.y = y;
}

void TransformComponent::move(Vec2f change)
{
    mPosition += change;
}

vg::Vec2f TransformComponent::getSize()
{
    return mSize;
}

void TransformComponent::setSize(const vg::Vec2f size)
{
    mSize = size;
}

float TransformComponent::getLocalRotation()
{
    return mRotation;
}

float TransformComponent::getWorldRotation()
{

	if (mGameObject != nullptr)
	{
		if (mGameObject->getParent() == nullptr)
		{
			return getLocalRotation();
		}
		else
		{
			TransformComponent *transformComponent = mGameObject->getParent()->getComponent<TransformComponent>();
			if (transformComponent != nullptr)
			{
				float parentRot= transformComponent->getLocalRotation();
				
				float tempRot= parentRot + getLocalRotation();

				

				return tempRot;
			}
		}
	}
	return getLocalRotation();
}

float TransformComponent::getRotation()
{
	return getWorldRotation();
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

void TransformComponent::setLayer(LayerGroup layer)
{
	mCurrentLayers[layer]++;
	if (mCurrentLayers[layer] > mLayerMaxValues[layer])
		mCurrentLayers[layer] = mLayerMinValues[layer];
	mLayer = mCurrentLayers[layer];
}

TransformComponent::LayerGroup TransformComponent::getLayerGroup()
{
	return mLayerGroup;
}

vg::Vec2f TransformComponent::getOrigin()
{
    return mOrigin;
}

void TransformComponent::setOrigin(const Vec2f origin)
{
    mOrigin = origin;
}

void TransformComponent::setUsingCamera(bool value)
{
	mUsingCamera = value;
}

bool TransformComponent::getUsingCamera()
{
	return mUsingCamera;
}

bool TransformComponent::contains(Vec2f point)
{
	Vec2f pos = getWorldPosition() - getOrigin();
	if (point.x > pos.x && point.y > pos.y)
	{
		pos += mSize;
		if (point.x < pos.x && point.y < pos.y)
			return true;
	}
	return false;
}


//private

float TransformComponent::getMaxLayer()
{
	return mLayerMaxValues[TOP];
}

float TransformComponent::getLayer()
{
	return static_cast<float>(mLayer);
}