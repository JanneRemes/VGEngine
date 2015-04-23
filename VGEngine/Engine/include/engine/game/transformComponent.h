#pragma once
#include "engine/game/component.h"
#include "engine/utility/Vector2.h"
namespace vg
{

	/**
	Component for managing gameObject by rotating or scaling
	*/
	class TransformComponent :
		public Component
	{
	public:
		TransformComponent();
		TransformComponent(float x, float y,float rotation = 0.0f);
		~TransformComponent();
		//float getX(){ return mX; };
		//float getY(){ return mY; };

		/**
		@return Returns rotation angle
		*/
		float getRotation(){ return mRotation; };
		//void setX(float x){ mX = x; };
		//void setY(float y){ mY = y; };

		/**
		Sets rotation angle
		@param rotation Angle that the object will be rotated by
		*/
		void setRotation(float rotation){ mRotation = rotation; };

		Vector2<float> mPosition; ///< Position of the object
		float mScale;			///< Size scale of the object

		/**
		Update of the transformComponent
		*/
		void update();
	private:

		//float mX;
		//float mY;
		float mRotation; ///< Rotation angle
	};

}