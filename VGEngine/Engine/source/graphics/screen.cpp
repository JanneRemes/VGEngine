
#include "engine/graphics/screen.h"
#include "engine/graphics/camera.h"

using namespace vg;
using namespace vg::graphics;

Vector2<int> Screen::mSize(1280, 720);
Vector2<int> Screen::mVirtualSize(1280, 720);

Vector2<int> Screen::getSize()
{
	return mSize;
}

vg::Vector2<int> Screen::getVirtualSize()
{
	return mVirtualSize;
}

int Screen::getX()
{
	return mSize.getX();
}

int Screen::getY()
{
	return mSize.getY();
}
 
void Screen::setSize(int x, int y)
{
	mSize = Vector2<int>(x, y);
}

void Screen::setVirtualSize(int x, int y)
{
	mVirtualSize = Vector2<int>(x, y);
}

Vector2<float> Screen::toWorld(float x, float y)
{
	Vector2<int> screen = Screen::getSize();
	Vector2<float> lt (Camera::mLeft, Camera::mTop);
	Vector2<float> rb (Camera::mRight, Camera::mBottom);
	float width = rb.getX() - lt.getX();
	float height = rb.getY() - lt.getY();
	return lt + Vector2<float>(x * (width / screen.getX()), y * (height / screen.getY()));
}

Vector2<float> Screen::toWorld(Vector2<float> input)
{
	return toWorld(input.getX(), input.getY());
}