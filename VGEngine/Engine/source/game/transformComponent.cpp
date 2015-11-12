
#include "engine/game/transformComponent.h"
#include "engine/game/gameObject.h"
#include "engine/utility/math.h"
#include "../external/glm/gtc/matrix_transform.hpp"

#include <math.h>  
#include <stdlib.h>

using namespace vg;

/// values used for tracking reserved layers
static unsigned int mCurrentLayers[] = { 1, 10000, 20000, 80000, 90000 };
static unsigned int mLayerMinValues[] = { 1, 10000, 20000, 80000, 90000 };
static unsigned int mLayerMaxValues[] = { 9999, 19999, 79999, 89999, 100000 };

TransformComponent::TransformComponent(): Component()
{
    mPosition = Vector2<float>(0, 0);
	mSize = Vector2<float>(0, 0);
    mRotation = 0.0f;
    mLayer = 0u;
	mOrigin = Vector2<float>(0, 0);
}

TransformComponent::TransformComponent(const TransformComponent &transform)
{
	mPosition = transform.mPosition;
	mSize = transform.mSize;
	mRotation = transform.mRotation;
	mLayer = transform.mLayer;
	mOrigin = transform.mOrigin;
	mUsingCamera = transform.mUsingCamera;
}

TransformComponent::TransformComponent(vg::Vector2<float> position, vg::Vector2<float> size,
	float rotation, vg::Vector2<float> origin, Layer layer, bool useCamera)
	:Component(), mPosition(position), mSize(size), mRotation(rotation), mOrigin(origin), mUsingCamera(useCamera)
{
	setLayer(layer);
}

TransformComponent::TransformComponent(vg::Vec2f position, vg::Vec2f size, float rotation, vg::Vec2f origin)
: mPosition(Vector2<float>(position.x, position.y)), mSize(Vector2<float>(size.x, size.y)), mRotation(rotation), mOrigin(Vector2<float>(origin.x, origin.y))
{
	setLayer(MIDDLE);
	mUsingCamera = true;
}

TransformComponent::~TransformComponent()
{
}

vg::Vector2<float> TransformComponent::getLocalPosition()
{
    return mPosition;
}
//TODO fix
vg::Vector2<float> TransformComponent::getWorldPosition()
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
				vg::Vector2<float> parentPos = transformComponent->getLocalPosition();
				vg::Vector2<float> parentOrigo = transformComponent->getOrigin();
				vg::Vector2<float> tempPos = parentPos + parentOrigo /*+ getLocalPosition()*/;
			
				float rotation = transformComponent->getLocalRotation();

				vg::Vector2<float> vector = getLocalPosition() -tempPos;
				glm::mat4 transu;
				transu = glm::rotate(transu, glm::radians(rotation), glm::vec3(0, 0, 1.0f));
				glm::vec4 result = transu * glm::vec4(vector.getX(), vector.getY(), 0.0f, 1.0f);
				vg::Vector2<int> syopa = vg::Vector2<int>(result.x, result.y);

				return tempPos;
			}
		}
	}
	

	return mPosition;
}
void TransformComponent::setPosition(const Vector2<float> position)
{
    mPosition = position;
}

void TransformComponent::setPosition(const Vec2f position)
{
	mPosition = Vector2<float>(position.x, position.y);
}

void TransformComponent::move(Vector2<float> change)
{
    mPosition += change;
}

vg::Vector2<float> TransformComponent::getSize()
{
    return mSize;
}

void TransformComponent::setSize(const vg::Vector2<float> size)
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
	return static_cast<float>(mLayer);
}

void TransformComponent::setLayer(Layer layer)
{
	mCurrentLayers[layer]++;
	if (mCurrentLayers[layer] > mLayerMaxValues[layer])
		mCurrentLayers[layer] = mLayerMinValues[layer];
	mLayer = mCurrentLayers[layer];
}

vg::Vector2<float> TransformComponent::getOrigin()
{
    return mOrigin;
}

void TransformComponent::setOrigin(const Vector2<float> origin)
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

bool TransformComponent::contains(Vector2<float> point)
{
	Vector2<float> pos = getWorldPosition() - getOrigin();
	if (point.getX() > pos.getX() && point.getY() > pos.getY())
	{
		pos += mSize;
		if (point.getX() < pos.getX() && point.getY() < pos.getY())
			return true;
	}
	return false;
}
