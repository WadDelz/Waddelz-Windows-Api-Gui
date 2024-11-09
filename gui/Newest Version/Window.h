#ifndef __WINDOW_H
#define __WINDOW_H

#include "Element.h"
#include "Menu.h"

#pragma once

#ifndef DEF_FLAGS_WINDOW
#define DEF_FLAGS_WINDOW WS_OVERLAPPEDWINDOW
#endif

namespace gui
{
	class Window : public Element
	{
		DECLARE_ELEMENT_NOSUBPROC(Window, Element)

		//Doesnt Make The Window
		Window();

		//Makes The Window
		Window(const char* title);
		Window(const char* classname, const char* wndprocname, const char* title, int flags, int x, int y, int w, int h, bool bPaintBg, unsigned char r, unsigned char g, unsigned char b, HICON icon, HINSTANCE instance);

		virtual void OnClose(ELEMENT_PROC_ITEMS);

		virtual HBRUSH GetBackgroundBrush();

		virtual Menu* GetThisMenu();
		virtual void SetThisMenu(Menu* menu);

		virtual void DeleteThisMenu();

		virtual void SetSizable(const bool& bSizable);
		virtual void SetCloseButtonEnable(const bool& bEnabled);

		DECLARE_ELEMENT_PROC();
	protected:
		virtual bool MakeWindow(const char* wndprocname, const char* title, long flags = DEF_FLAGS_WINDOW, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int w = 800, int h = 600, bool bPaintBg = false, unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, HICON icon = nullptr, HINSTANCE instance = GetModuleHandle(nullptr));

		Menu* m_Menu;
		HBRUSH m_hbBackground;
	};
}

#endif //__WINDOW_H