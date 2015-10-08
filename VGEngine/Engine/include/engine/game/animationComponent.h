#pragma once
#include "engine/game/component.h"
namespace vg
{
	class AnimationComponent :
		public Component
	{

		friend class AnimationSystem;
	public:
		AnimationComponent(float mAnimationInterval, int frameRowCount, int FrameColumnCount, int frameWidth, int frameHeight);
		~AnimationComponent();
		
	protected:

		//float mTexCoords[8];
		float mAnimationInterval;
		int mFrameTotalCount;
		int mFrameRowCount;
		int mFrameColumnCount;
		int mFrameWidth;
		int mFrameHeight;

		float mXOffSet;
		float mYOffSet;

		bool isInitialized;
	};
}