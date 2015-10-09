#pragma once
#include "engine/game/component.h"
namespace vg
{
	class AnimationComponent :
		public Component
	{

		friend class AnimationSystem;
	public:
		AnimationComponent(float mAnimationInterval, int frameRowCount, int frameColumnCount, int frameTotalCount, int frameWidth, int frameHeight);
		~AnimationComponent();
		
	protected:
	
		int mFrameTotalCount;
		int mFrameRowCount;
		int mFrameColumnCount;
		int mFrameWidth;
		int mFrameHeight;
		float mAnimationInterval;
		float mAnimationTimer;

		int mXOffSetIndex;
		int mYOffSetIndex;
		int mFrameIndex;
		float mXOffSet;
		float mYOffSet;

		bool isInitialized;
	};
}