#include "engine\game\animationComponent.h"

using namespace vg;

AnimationComponent::AnimationComponent(float animationInterval, int frameRowCount, int frameColumnCount, int frameTotalCount) : Component()
{
	mAnimationInterval = animationInterval;
	mFrameRowCount = frameRowCount;
	mFrameTotalCount = frameTotalCount;

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