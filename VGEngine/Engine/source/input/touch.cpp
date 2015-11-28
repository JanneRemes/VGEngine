
#include "engine/input/touch.h"
#include "engine/graphics/screen.h"

using namespace vg;
using namespace vg::input;
using namespace vg::graphics;

bool Touch::mIsTouched = false;
bool Touch::mIsTouchReleased = false;
Vec2f Touch::mPos = Vec2f();


Vec2f Touch::getPos(bool relativeToCamera)
{
	if (relativeToCamera)
		return Screen::toWorld(mPos);
	else
		return Screen::realToVirtual(mPos);
}

void Touch::setPos(Vec2f value)
{
	mPos = value;
}

bool Touch::getIsTouched()
{
	return mIsTouched;
}

bool Touch::getIsReleased()
{
	return mIsTouchReleased;
}

void Touch::update()
{
	if (mIsTouchReleased)
		mIsTouchReleased = false;
}

void Touch::setIsTouched(bool value)
{
	mIsTouched = value;
}

void Touch::setIsReleased(bool value)
{
	mIsTouchReleased = value;
}

Vec2f Touch::fromCenter()
{
	Vec2f result(0.5f * Screen::getSize().x, 0.5f * Screen::getSize().y);
	Vec2f input = getPos(false);
	result -= input;
	result *= -1.0f;
	return result;
}
