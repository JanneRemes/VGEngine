#include "engine\game\animationComponent.h"

using namespace vg;

AnimationComponent::AnimationComponent(float animationInterval, int frameRowCount, int frameColumnCount, int frameTotalCount, int frameWidth, int frameHeight) : Component()
{
	mAnimationInterval = animationInterval;
	mFrameRowCount = frameRowCount;
	mFrameTotalCount = frameTotalCount;
	mFrameWidth = frameWidth;
	mFrameHeight = frameHeight;
	mFrameColumnCount = frameColumnCount;

	mXOffSet = 0.0f;
	mYOffSet = 0.0f;
	mXOffSetIndex = 0;
	mYOffSetIndex = 0;
	mFrameIndex = 0;
	mAnimationTimer = 0.0f;

	isInitialized = false;
}

AnimationComponent::~AnimationComponent()
{

}