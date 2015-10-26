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

vg::Vector2<float> Mouse::getMousePos()
{
	POINT pt;
	GetCursorPos(&pt);
	HWND handle = static_cast<HWND>(Game::getInstance()->getGraphics()->getContext()->mWindowHandle);
	ScreenToClient(handle, &pt);
	return Screen::toWorld(pt.x, pt.y);
}

#endif