#include "Screen.h"

void gui::GetScreenSize(int* wide, int* tall)
{
	if (wide)
		*wide = GetSystemMetrics(SM_CXSCREEN);

	if (tall)
		*tall = GetSystemMetrics(SM_CYSCREEN);
}