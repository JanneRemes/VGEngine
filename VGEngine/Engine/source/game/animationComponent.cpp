#include "engine\game\animationComponent.h"

using namespace vg;

AnimationComponent::AnimationComponent(float animationInterval, int frameCount, int frameWidth, int frameHeight) : Component()
{
	mAnimationInterval = animationInterval;
	mFrameCount = frameCount;
	mFrameWidth = frameWidth;
	mFrameHeight = frameHeight;
}

AnimationComponent::~AnimationComponent()
{

}