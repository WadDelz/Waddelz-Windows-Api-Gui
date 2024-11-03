#ifndef __PAINT_H
#define __PAINT_H

#include <Windows.h>

#pragma once

#define PAINT_START(hwnd, r, g, b)					\
PAINTSTRUCT ps##hwnd;								\
HDC hdc##hwnd = BeginPaint(hwnd, &ps##hwnd);		\
HBRUSH brush##hwnd = CreateSolidBrush(RGB(r,g,b));	\
RECT rect##hwnd{0,0,0,0};							\

#define PAINT_SETCOLOR(hwnd, r, g, b)			\
DeleteObject(brush##hwnd);						\
brush##hwnd = CreateSolidBrush(RGB(r,g,b));

#define PAINT_FILL_RECT(hwnd, left1, top1, right1, bottom1)	\
rect##hwnd.left = left1;									\
rect##hwnd.top = top1;										\
rect##hwnd.right = right1;									\
rect##hwnd.bottom = bottom1;								\
FillRect(hdc##hwnd, &rect##hwnd, brush##hwnd);

#define PAINT_DRAW_LINE(hwnd, x1, y1, x2, y2, r, g, b, thickness)  \
HPEN pen##hwnd = CreatePen(PS_SOLID, thickness, RGB(r, g, b)); \
SelectObject(hdc##hwnd, pen##hwnd);                            \
MoveToEx(hdc##hwnd, x1, y1, NULL);                             \
LineTo(hdc##hwnd, x2, y2);                                     \
DeleteObject(pen##hwnd);

#define PAINT_FILL(hwnd)									\
FillRect(hdc##hwnd, &rect##hwnd, brush##hwnd);				

#define PAINT_SET_CLIENT_RECT(hwnd)							\
GetClientRect(hwnd, &rect##hwnd);

#define PAINT_END(hwnd)							\
DeleteObject(brush##hwnd);						\
EndPaint(hwnd, &ps##hwnd);

//ERASE BACKGROUND
#define PAINT_BACKGROUND_START(hwnd, r, g, b)					\
HDC hdc##hwnd = (HDC)wp;										\
RECT rect##hwnd{0,0,0,0};										\
HBRUSH brush##hwnd = CreateSolidBrush(RGB(r,g,b));				\

#define PAINT_BACKGROUND_END(hwnd)							\
DeleteObject(brush##hwnd);

#define PAINT_SET_PIXEL(hwnd, x, y, r, g, b) \
SetPixel(hdc##hwnd, x, y, RGB(r, g, b));

#endif