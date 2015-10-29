
#include "engine/input/touch.h"
#include "engine/graphics/screen.h"

using namespace vg;
using namespace vg::input;
using namespace vg::graphics;

bool Touch::mIsTouched = false;
bool Touch::mIsTouchReleased = false;
Vector2<float> Touch::mPos = Vector2<float>();


Vector2<float> Touch::getPos()
{
	return Screen::toWorld(mPos);
}

void Touch::setPos(Vector2<float> value)
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
