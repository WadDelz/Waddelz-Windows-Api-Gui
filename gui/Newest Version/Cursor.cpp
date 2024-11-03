#include "Cursor.h"

POINT gui::GetCursorPosition()
{
	POINT pt = { 0,0 };
	GetCursorPos(&pt);
	return pt;
}

void gui::SetCursorPosition(POINT pt)
{
	SetCursorPos(pt.x, pt.y);
}

void gui::SetCursorPosition(int x, int y)
{
	SetCursorPos(x, y);
}

bool gui::IsMouseButtonHeldDown(short button)
{
	int key = button == 0 ? VK_LBUTTON : button == 1 ? VK_MBUTTON : VK_RBUTTON;
	return (GetAsyncKeyState(key) == 0x8000);
}
