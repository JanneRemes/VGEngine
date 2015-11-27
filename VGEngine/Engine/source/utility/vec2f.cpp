
#include "engine/utility/vec2f.h"
#include "engine/utility/math.h"

#include <math.h>

using namespace vg;

Vec2f::Vec2f()
{
	x = y = 0.0f;
}

Vec2f::Vec2f(float _x, float _y)
: x(_x), y(_y)
{
}

Vec2f::Vec2f(float both)
{
	x = y = both;
}

Vec2f::Vec2f(const Vec2f& other)
{
	x = other.x;
	y = other.y;
}

float Vec2f::distance(Vec2f other)
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

float Vec2f::distance(Vec2f a, Vec2f b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float Vec2f::length()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Vec2f::length(const Vec2f& vec)
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

void Vec2f::normalize()
{
	x /= length();
	y /= length();
}

Vec2f Vec2f::normalize(const Vec2f& vec)
{
	Vec2f result(vec);
	result.normalize();
	return result;
}

float Vec2f::dot(const Vec2f& a, const Vec2f& b)
{
	return a.x * b.x + a.y * b.y;
}

float Vec2f::angle(const Vec2f& a, const Vec2f& b)
{
	return Math::radianToDegrees(acos(dot(a, b) / (length(a) * length(b))));
}

//operators
Vec2f Vec2f::operator + (const Vec2f& right)
{
	return Vec2f(x + right.x, y + right.y);
}

Vec2f Vec2f::operator- (const Vec2f& right)
{
	return Vec2f(x - right.x, y - right.y);
}

Vec2f Vec2f::operator += (const Vec2f& right)
{
	x += right.x;
	y += right.y;
	return *this;
}

Vec2f Vec2f::operator -= (const Vec2f& right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}

Vec2f Vec2f::operator *= (const float& right)
{
	x *= right;
	y *= right;
	return *this;
}

Vec2f Vec2f::operator /= (const float& right)
{
	x /= right;
	y /= right;
	return *this;
}

bool Vec2f::operator == (const Vec2f& right)
{
	return x == right.x && y == right.y;
}

bool Vec2f::operator != (const Vec2f& right)
{
	return x != right.x || y != right.y;
}

