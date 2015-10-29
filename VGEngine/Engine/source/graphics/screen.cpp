
#include "engine/graphics/screen.h"
#include "engine/graphics/camera.h"

using namespace vg;
using namespace vg::graphics;

Vector2<int> Screen::mSize(1280, 720);
Vector2<int> Screen::mRealSize(1280, 720);

Vector2<int> Screen::getSize()
{
	return mSize;
}

vg::Vector2<int> Screen::getRealSize()
{
	return mRealSize;
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

Vector2<float> Screen::toWorld(float x, float y)
{
	Vector2<float> input = realToVirtual(x, y);
	Vector2<int> screen = Screen::getSize();
	Vector2<float> lt (Camera::mLeft, Camera::mTop);
	Vector2<float> rb (Camera::mRight, Camera::mBottom);
	float width = rb.getX() - lt.getX();
	float height = rb.getY() - lt.getY();
	return lt + Vector2<float>(input.getX() * (width / screen.getX()),
		input.getY() * (height / screen.getY()));
}

Vector2<float> Screen::toWorld(Vector2<float> input)
{
	return toWorld(input.getX(), input.getY());
}

Vector2<float> Screen::realToVirtual(Vector2<float> input)
{
	Vector2<float> scale(getX() / static_cast<float>(mRealSize.getX()),
		getY() / static_cast<float>(mRealSize.getY()));
	return Vector2<float>(scale.getX() * input.getX(), scale.getY() * input.getY());
}

Vector2<float> Screen::realToVirtual(float x, float y)
{
	return realToVirtual(Vector2<float>(x, y));
}


//private

void Screen::setRealSize(int x, int y)
{
	mRealSize = Vector2<int>(x, y);
}