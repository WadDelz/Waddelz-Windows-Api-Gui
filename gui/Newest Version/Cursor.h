#ifndef __CURSER_H
#define __CURSER_H

#include <Windows.h>

#pragma once

namespace gui
{
	POINT GetCursorPosition();

	void SetCursorPosition(POINT pt);
	void SetCursorPosition(int x, int y);

	//0 = left 1 = middle 2 = right
	bool IsMouseButtonHeldDown(short button);
}

#endif