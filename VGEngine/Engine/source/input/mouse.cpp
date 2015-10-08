#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include <Windows.h>
#include "engine/game/game.h"
using namespace vg::input;
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
	vg::Vector2<float> tempVector(pt.x,pt.y);
	return tempVector;
}

#endif