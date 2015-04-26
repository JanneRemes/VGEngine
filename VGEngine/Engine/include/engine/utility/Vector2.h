#pragma once
#include "engine/utility/logger.h"
#include <math.h> 
namespace vg
{
	template <typename T>
	class Vector2
	{
	public:
		T getX(){ return mX; };
		T getY(){ return mY; };
		void setX(T x){ mX = x; };
		void setY(T y){ mY = y; };
		void setXY(T x, T y){ mX = x; mY = y; };

		static float Distance(Vector2<T> vector1, Vector2<T> vector2)
		{
			T a = pow(vector2.mX - vector1.mX, 2);
			T b = pow(vector2.mY - vector1.mY, 2);
			return sqrt(a + b);
		}

		Vector2() = default;

		Vector2(T X, T Y)
		{
			mX = X; mY = Y;
		}
		Vector2<T> operator + (const Vector2<T>& right)
		{
			mX = mX + right.getX();
			mY = mY + right.getY();
			return *this;
		}
		Vector2<T> operator - (const Vector2<T>& right)
		{
			mX = mX - right.getX();
			mY = mY - right.getY();
			return *this;
		}
		bool operator == (const Vector2<T>& right)
		{
			return mX == right.getX() && mY == right.getY();
		}

		Vector2<T> operator *=(Vector2<T>& left)
		{
			mX *= left.getX();
			mY *= left.getY();
			return *this;
		}
		Vector2<T> operator /=(Vector2<T>& left)
		{
			mX /= left.getX();
			mY /= left.getY();
			return *this;
		}
		Vector2<T> operator +=(Vector2<T>& left)
		{
			mX += left.getX();
			mY += left.getY();
			return *this;
		}
		Vector2<T> operator -=(Vector2<T>& left)
		{
			mX -= left.getX();
			mY -= left.getY();
			return *this;
		}
		void log()
		{
			Log("vector", "Vector x: %f, y: %f", mX, mY);
		}
	private:
		T mX;
		T mY;
	};






};