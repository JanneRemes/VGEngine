
#ifdef OS_WINDOWS

#include "engine/input/mouse.h"
#include "engine/game/game.h"
#include "engine/graphics/screen.h"

#include <Windows.h>

using namespace vg;
using namespace vg::input;
using namespace vg::graphics;

static bool state[] = { false, false, false };
static bool lastState[] = { false, false, false };

bool Mouse::isKeyPressed(MOUSE_KEY key)
{
	return !isKeyDown(key) && lastState[key];
}

bool Mouse::isKeyDown(MOUSE_KEY key)
{
	return state[key];
}

Vector2<float> Mouse::getPos(bool relativeToCamera)
{
	POINT pt;
	GetCursorPos(&pt);
	HWND handle = static_cast<HWND>(Game::getInstance()->getGraphics()->getContext()->getWindowHandle());
	ScreenToClient(handle, &pt);
	if (relativeToCamera)
		return Screen::toWorld(pt.x, pt.y);
	else 
		return Vector2<float>(pt.x, pt.y);
}

Vector2<float> Mouse::fromCenter()
{
	Vector2<float> result(0.5f * Screen::getSize().getX(), 0.5f * Screen::getSize().getY());
	result -= getPos(false);
	result.normalize();
	result *= -1.0f;
	return result;
}

void Mouse::update()
{
	lastState[LEFT] = state[LEFT];
	lastState[RIGHT] = state[RIGHT];
	lastState[MIDDLE] = state[MIDDLE];

	state[LEFT] = keyDown(LEFT);
	state[RIGHT] = keyDown(RIGHT);
	state[MIDDLE] = keyDown(MIDDLE);
}


//private

bool Mouse::keyDown(MOUSE_KEY key)
{
	HWND handle = static_cast<HWND>(Game::getInstance()->getGraphics()->getContext()->getWindowHandle());
	if (GetActiveWindow() != handle)
		return false;
	int vkey = 0;
	switch (key)
	{
	case LEFT:
		vkey = VK_LBUTTON;
		break;
	case RIGHT:
		vkey = VK_RBUTTON;
		break;
	case MIDDLE:
		vkey = VK_MBUTTON;
		break;
	default:
		return false;
	}
	return(GetAsyncKeyState(vkey) != 0);
}

#endif