#ifdef OS_WINDOWS

#include "engine/input/mouse.h"
#include "engine/game/game.h"
#include "engine/graphics/screen.h"

#include <Windows.h>

using namespace vg;
using namespace vg::input;
using namespace vg::graphics;

bool Mouse::isKeyPressed(MOUSE_KEY key)
{
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
	return(GetAsyncKeyState(vkey) & 0x8000 != 0);
}

bool Mouse::isKeyDown(MOUSE_KEY key)
{
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

Vector2<float> Mouse::getPos(bool relativeToCamera)
{
	POINT pt;
	GetCursorPos(&pt);
	HWND handle = static_cast<HWND>(Game::getInstance()->getGraphics()->getContext()->mWindowHandle);
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

#endif