
#pragma once

#include "engine/game/component.h"

namespace vg
{
	/**
	Contains values needed for an animated sprite
	*/
	class AnimationComponent : public Component
	{
		friend class AnimationSystem;
		friend class RenderSystem;

	public:
		/**
		@param mAnimationInterval time before changing to next frame
		@param frameRowCount number of frame rows
		@param frameColumnCount number of frame colums
		@param frameTotalCount number of frames
		*/
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