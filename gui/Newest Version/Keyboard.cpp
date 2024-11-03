#include "Keyboard.h"

bool gui::IsKeyHeldDown(KeyboardKey key)
{
	return (GetAsyncKeyState((int)key) & 0x8000) != 0;
}

bool gui::IsKeyToggleStateOn(KeyboardKey key)
{
	return (GetKeyState((int)key) & 0x0001) != 0;
}
