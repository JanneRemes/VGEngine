#pragma once
#include "engine/game/component.h"
namespace vg
{
	class AnimationComponent :
		public Component
	{
	public:
		AnimationComponent(float mAnimationInterval, int frameCount, int frameWidth, int frameHeight);
		~AnimationComponent();
		float getAnimationInterval() {return mAnimationInterval; }
		int getFrameCount(){ return mFrameCount; }
		int getFrameWidth(){ return mFrameWidth; }
		int getFrameheight(){ return mFrameHeight; }
		
	private:

		//float mTexCoords[8];
		float mAnimationInterval;
		int mFrameCount;
		int mFrameWidth;
		int mFrameHeight;
	};
}