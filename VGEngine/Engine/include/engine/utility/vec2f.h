
#pragma once

#include "engine/utility/vec2f.h"

namespace vg
{
	/**
	2D float vector, simple alternative to Vector2<T>
	*/
	class Vec2f
	{
	public:
		
		Vec2f();
		Vec2f(float _x, float _y);
		Vec2f(float both);

		~Vec2f() = default;

		/**
		@param other compared vector
		@return absolute distance between vectors
		*/
		float distance(Vec2f other);

		/**
		@param ab compared vectors
		@return absolute distance between vectors
		*/
		static float distance(Vec2f a, Vec2f b);

		/**
		@return length of the vector
		*/
		float length();

		/**
		Converts the vector to a unit vector
		*/
		void normalize();

		Vec2f operator + (const Vec2f& right);
		Vec2f operator - (const Vec2f& right);
		Vec2f operator += (const Vec2f& right);
		Vec2f operator -= (const Vec2f& right);
		Vec2f operator *= (const float& right);
		Vec2f operator /= (const float& right);
		bool operator == (const Vec2f& right);
		bool operator != (const Vec2f& right);

		float x;	///< x-axis value
		float y;	///< y-axis value
	};
}