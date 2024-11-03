#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <Windows.h>

#pragma once

namespace gui
{
	enum class KeyboardKey
	{
		Key_A = 'A',
		Key_B = 'B',
		Key_C = 'C',
		Key_D = 'D',
		Key_E = 'E',
		Key_F = 'F',
		Key_G = 'G',
		Key_H = 'H',
		Key_I = 'I',
		Key_J = 'J',
		Key_K = 'K',
		Key_L = 'L',
		Key_M = 'M',
		Key_N = 'N',
		Key_O = 'O',
		Key_P = 'P',
		Key_Q = 'Q',
		Key_R = 'R',
		Key_S = 'S',
		Key_T = 'T',
		Key_U = 'U',
		Key_V = 'V',
		Key_W = 'W',
		Key_X = 'X',
		Key_Y = 'Y',
		Key_Z = 'Z',

		Key_1 = '1',
		Key_2 = '2',
		Key_3 = '3',
		Key_4 = '4',
		Key_5 = '5',
		Key_6 = '6',
		Key_7 = '7',
		Key_8 = '8',
		Key_9 = '9',
		Key_0 = '0',

		Key_LCtrl = VK_LCONTROL,
		Key_RCtrl = VK_RCONTROL,
		Key_Ctrl = VK_CONTROL,
		Key_LShift = VK_LSHIFT,
		Key_RShift = VK_RSHIFT,
		Key_LAlt = VK_LMENU,
		Key_RAlt = VK_RMENU,
		Key_Alt = VK_MENU,
		Key_LWin = VK_LWIN,
		Key_RWin = VK_RWIN,
		Key_CapsLock = VK_CAPITAL,
		Key_Tab = VK_TAB,
		Key_Tilde = VK_OEM_3,
		Key_Space = VK_SPACE,
		Key_Enter = VK_RETURN,
		Key_Backspace = VK_BACK,
		Key_Escape = VK_ESCAPE,

		Key_Arrow_Up = VK_UP,
		Key_Arrow_Down = VK_DOWN,
		Key_Arrow_Left = VK_LEFT,
		Key_Arrow_Right = VK_RIGHT,

		Key_PageUp = VK_PRIOR,
		Key_PageDown = VK_NEXT,
		Key_Home = VK_HOME,
		Key_End = VK_END,
		Key_Insert = VK_INSERT,
		Key_Delete = VK_DELETE,

		Key_F1 = VK_F1,
		Key_F2 = VK_F2,
		Key_F3 = VK_F3,
		Key_F4 = VK_F4,
		Key_F5 = VK_F5,
		Key_F6 = VK_F6,
		Key_F7 = VK_F7,
		Key_F8 = VK_F8,
		Key_F9 = VK_F9,
		Key_F10 = VK_F10,
		Key_F11 = VK_F11,
		Key_F12 = VK_F12,

		Key_NumLock = VK_NUMLOCK,
		Key_NumPad0 = VK_NUMPAD0,
		Key_NumPad1 = VK_NUMPAD1,
		Key_NumPad2 = VK_NUMPAD2,
		Key_NumPad3 = VK_NUMPAD3,
		Key_NumPad4 = VK_NUMPAD4,
		Key_NumPad5 = VK_NUMPAD5,
		Key_NumPad6 = VK_NUMPAD6,
		Key_NumPad7 = VK_NUMPAD7,
		Key_NumPad8 = VK_NUMPAD8,
		Key_NumPad9 = VK_NUMPAD9,
		Key_NumPadAdd = VK_ADD,
		Key_NumPadSubtract = VK_SUBTRACT,
		Key_NumPadMultiply = VK_MULTIPLY,
		Key_NumPadDivide = VK_DIVIDE,

		Key_Semicolon = VK_OEM_1,
		Key_Equal = VK_OEM_PLUS,
		Key_Comma = VK_OEM_COMMA,
		Key_Minus = VK_OEM_MINUS,
		Key_Period = VK_OEM_PERIOD,
		Key_Slash = VK_OEM_2,
		Key_Backslash = VK_OEM_5,
		Key_Quote = VK_OEM_7,
		Key_LeftBracket = VK_OEM_4,
		Key_RightBracket = VK_OEM_6,
	};

	bool IsKeyHeldDown(KeyboardKey key);
	bool IsKeyToggleStateOn(KeyboardKey key);
}


#endif