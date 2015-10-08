#include "engine\game\animationComponent.h"

using namespace vg;

AnimationComponent::AnimationComponent(float animationInterval, int frameRowCount, int frameColumnCount, int frameWidth, int frameHeight) : Component()
{
	mAnimationInterval = animationInterval;
	mFrameRowCount = frameRowCount;
	mFrameColumnCount = frameColumnCount;
	mFrameWidth = frameWidth;
	mFrameHeight = frameHeight;
	mFrameTotalCount = frameColumnCount + frameRowCount;

	isInitialized = false;
}

AnimationComponent::~AnimationComponent()
{

}