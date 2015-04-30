
#include "engine/game/transformComponent.h"
#include <stdlib.h> 

using namespace vg;

TransformComponent::TransformComponent(): Component()
{
    mPosition = Vector2<int>(0, 0);
    mSize = Vector2<int>(0, 0);
    mRotation = 0.0f;
    mLayer = 0u;
    mOrigin = Vector2<int>(0, 0);
}

TransformComponent::TransformComponent(vg::Vector2<int> position, vg::Vector2<int> size,
    float rotation, uint layer, vg::Vector2<int> origin)
    :Component(), mPosition(position), mSize(size), mRotation(rotation), mLayer(layer), mOrigin(origin)
{
}

TransformComponent::~TransformComponent()
{
}

vg::Vector2<int> TransformComponent::getPosition()
{
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

void TransformComponent::setRotation(float rotation)
{
    mRotation = rotation;
}

void TransformComponent::rotate(float rotation)
{
    setRotation(mRotation + rotation);
}

uint TransformComponent::getLayer()
{
    return mLayer;
}

void TransformComponent::setLayer(uint layer)
{
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