#ifndef __ICON_H
#define __ICON_H

#include <Windows.h>

#pragma once

namespace gui
{
	HBITMAP CreateBitmapFromIcon(HICON hIcon);

	HICON LoadIconFromFile(const char* path, int width = 16, int height = 16, int flags = IMAGE_ICON, int loadtype = LR_LOADFROMFILE);
	//HICON CropIcon(HICON hIcon, int x, int y, int width, int height);
}

#endif