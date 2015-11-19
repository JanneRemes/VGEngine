
#include "engine/graphics/screen.h"
#include "engine/graphics/camera.h"

using namespace vg;
using namespace vg::graphics;

Vec2f Screen::mSize(1280, 720);
Vec2f Screen::mRealSize(1280, 720);
Color Screen::mColor = Color();

Vec2f Screen::getSize()
{
	return mSize;
}

vg::Vec2f Screen::getRealSize()
{
	return mRealSize;
}

int Screen::getX()
{
	return mSize.x;
}

int Screen::getY()
{
	return mSize.y;
}
 
void Screen::setSize(int x, int y)
{
	mSize = Vec2f(x, y);
}

Vec2f Screen::toWorld(float x, float y)
{
	Vec2f input = realToVirtual(x, y);
	Vec2f screen = Screen::getSize();
	Vec2f lt (Camera::mLeft, Camera::mTop);
	Vec2f rb (Camera::mRight, Camera::mBottom);
	float width = rb.x - lt.x;
	float height = rb.y - lt.y;
	return lt + Vec2f(input.x * (width / screen.x),
		input.y * (height / screen.y));
}

Vec2f Screen::toWorld(Vec2f input)
{
	return toWorld(input.x, input.y);
}

Vec2f Screen::realToVirtual(Vec2f input)
{
	Vec2f scale(getX() / static_cast<float>(mRealSize.x),
		getY() / static_cast<float>(mRealSize.y));
	return Vec2f(scale.x * input.x, scale.y * input.y);
}

Vec2f Screen::realToVirtual(float x, float y)
{
	return realToVirtual(Vec2f(x, y));
}

void Screen::setColor(vg::Color color)
{
	mColor = color;
}

Color Screen::getColor()
{
	return mColor;
}

//private

void Screen::setRealSize(int x, int y)
{
	mRealSize = Vec2f(x, y);
}