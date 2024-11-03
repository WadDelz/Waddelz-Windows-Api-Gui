#include "Icon.h"

using namespace gui;

HICON gui::LoadIconFromFile(const char* path, int width, int height, int flags, int loadtype)
{
    return (HICON)LoadImage(
        nullptr,
        path,
        flags,
        width,
        height,
        loadtype
    );
}


HBITMAP gui::CreateBitmapFromIcon(HICON hIcon)
{
	ICONINFO iconInfo;
	HBITMAP hBitmap = nullptr;

	if (GetIconInfo(hIcon, &iconInfo))
	{
		hBitmap = iconInfo.hbmColor;
		DeleteObject(iconInfo.hbmMask);
	}
	return hBitmap;
}
