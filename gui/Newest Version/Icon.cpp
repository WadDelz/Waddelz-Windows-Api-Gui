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

//thanks chatgpt for this 1 function
//nevermind fuck you it doesnt work
//HICON gui::CropIcon(HICON hIcon, int x, int y, int width, int height)
//{
//    ICONINFO iconInfo;
//    if (!GetIconInfo(hIcon, &iconInfo))
//        return nullptr;
//
//    BITMAP bm;
//    if (!GetObject(iconInfo.hbmColor, sizeof(BITMAP), &bm))
//    {
//        DeleteObject(iconInfo.hbmColor);
//        DeleteObject(iconInfo.hbmMask);
//        return nullptr;
//    }
//
//    HDC hdcSrc = CreateCompatibleDC(nullptr);
//    HDC hdcDst = CreateCompatibleDC(nullptr);
//
//    HBITMAP hbmCropped = CreateCompatibleBitmap(hdcSrc, width, height);
//    HBITMAP hbmOldDst = (HBITMAP)SelectObject(hdcDst, hbmCropped);
//
//    HBITMAP hbmOldSrc = (HBITMAP)SelectObject(hdcSrc, iconInfo.hbmColor);
//    BitBlt(hdcDst, 0, 0, width, height, hdcSrc, x, y, SRCCOPY);
//
//    SelectObject(hdcSrc, hbmOldSrc);
//    SelectObject(hdcDst, hbmOldDst);
//    DeleteDC(hdcSrc);
//    DeleteDC(hdcDst);
//
//    ICONINFO croppedIconInfo = {};
//    croppedIconInfo.fIcon = TRUE;
//    croppedIconInfo.hbmColor = hbmCropped;
//    croppedIconInfo.hbmMask = iconInfo.hbmMask;
//
//    HICON hCroppedIcon = CreateIconIndirect(&croppedIconInfo);
//
//    DeleteObject(hbmCropped);
//    DeleteObject(iconInfo.hbmColor);
//    DeleteObject(iconInfo.hbmMask);
//
//    return hCroppedIcon;
//}
