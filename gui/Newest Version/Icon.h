#ifndef __ICON_H
#define __ICON_H

#include <Windows.h>

#pragma once

namespace gui
{
	HICON LoadIconFromFile(const char* path, int width = 16, int height = 16, int flags = IMAGE_ICON, int loadtype = LR_LOADFROMFILE);
	HBITMAP CreateBitmapFromIcon(HICON hIcon);

	//todo make icon showing class thinngy
}

#endif