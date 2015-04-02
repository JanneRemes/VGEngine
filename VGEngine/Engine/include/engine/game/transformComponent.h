#pragma once
#include "engine/game/component.h"
#include "engine/utility/Vector2.h"
namespace vg
{
	class TransformComponent :
		public Component
	{
	public:
		TransformComponent();
		TransformComponent(float x, float y,float rotation = 0.0f);
		~TransformComponent();
		//float getX(){ return mX; };
		//float getY(){ return mY; };
		float getRotation(){ return mRotation; };
		//void setX(float x){ mX = x; };
		//void setY(float y){ mY = y; };
		void setRotation(float rotation){ mRotation = rotation; };
		Vector2<float> mPosition;
		void update();
	private:

		//float mX;
		//float mY;
		float mRotation;
	};

}