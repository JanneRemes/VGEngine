
#pragma once

#include "engine/utility/vec2f.h"

namespace vg
{
	/**
	2D float vector
	*/
	class Vec2f
	{
	public:
		
		Vec2f();
		Vec2f(float _x, float _y);
		Vec2f(float both);
		Vec2f(const Vec2f& other);

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
		@return length of the vector
		*/
		static float length(const Vec2f& vec);

		/**
		Converts the vector to a unit vector
		*/
		void normalize();

		/**
		@return unit vector copy
		*/
		static Vec2f normalize(const Vec2f& vec);

		/**
		@return dot product
		*/
		static float dot(const Vec2f& a, const Vec2f& b);

		/**
		@return angle between vectors
		*/
		static float angle(const Vec2f& a, const Vec2f& b);

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