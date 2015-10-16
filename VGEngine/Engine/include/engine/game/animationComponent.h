#pragma once
#include "engine/game/component.h"
namespace vg
{
	class AnimationComponent :
		public Component
	{

		friend class AnimationSystem;
	public:
		AnimationComponent(float mAnimationInterval, int frameRowCount, int frameColumnCount, int frameTotalCount);
		~AnimationComponent();
		
	protected:
	
		int mFrameTotalCount;
		int mFrameRowCount;
		int mFrameColumnCount;
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