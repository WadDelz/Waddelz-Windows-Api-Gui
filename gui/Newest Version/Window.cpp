#include "Window.h"

using namespace gui;

START_ELEMENT_PROC(Window)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_PROC(CALL_DEF_WINDPROC())

Window::Window() : BaseClass()
{
	m_Menu = nullptr;
	m_hbBackground = nullptr;
	SetClassname("Window");
}

Window::Window(const char* title) : BaseClass()
{
	m_Menu = nullptr;
	m_hbBackground = nullptr;
	SetClassname("Window");
	MakeWindow("Window", title);
}

Window::Window(const char* classname, const char* wndprocname, const char* title, int flags, int x, int y, int w, int h, bool bPaintBg, unsigned char r, unsigned char g, unsigned char b, HICON icon, HINSTANCE instance) : BaseClass()
{
	m_Menu = nullptr;
	m_hbBackground = nullptr;
	SetClassname(classname);
	MakeWindow(wndprocname, title, flags, x, y, w, g, bPaintBg, r, g, b, icon, instance);
}

void Window::OnClose(ELEMENT_PROC_ITEMS)
{
	exit(0);
}

HBRUSH Window::GetBackgroundBrush()
{
	return m_hbBackground;
}

Menu* Window::GetThisMenu()
{
	return m_Menu;
}

void Window::SetThisMenu(Menu* menu)
{
	if (!menu)
		return;

	if (!menu->GetMenu())
		return;
	
	if (m_Menu)
		m_Menu->DeleteMenu();

	SetMenu(m_Hwnd, menu->GetMenu());
	m_Menu = menu;
	menu->SetParent(this);
}

void Window::DeleteThisMenu()
{
	if (!m_Menu)
		return;

	m_Menu->DeleteMenu();
	m_Menu = nullptr;
	SetMenu(m_Hwnd, nullptr);
}

void Window::SetSizable(const bool& bSizable)
{
	if (!bSizable)
		SetFlags(GetFlags() & ~WS_THICKFRAME);
	else
		SetFlags(GetFlags() | WS_THICKFRAME);
}

void Window::SetCloseButtonEnable(const bool& bEnabled)
{
	HMENU hMenu = GetSystemMenu(m_Hwnd, FALSE);
	if (!bEnabled)
		EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
	else
		EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
}

bool Window::MakeWindow(const char* wndprocname, const char* title, long flags, int x, int y, int w, int h, bool bPaintBg, unsigned char r, unsigned char g, unsigned char b, HICON icon, HINSTANCE instance)
{
	WNDCLASS wc = {};

	if (bPaintBg)
		wc.hbrBackground = m_hbBackground = CreateSolidBrush(RGB(r, g, b));

	wc.lpszClassName = wndprocname;
	wc.hInstance = instance;
	wc.lpfnWndProc = ElementProcBase;
	wc.hIcon = icon;

	if (!RegisterClass(&wc))
		return false;

	m_Hwnd = CreateWindow(
		wndprocname,
		title,
		flags,
		x, y,
		w, h,
		nullptr,
		nullptr,
		instance,
		nullptr
	);

	SET_ELEMENT_USERDATA(m_Hwnd, this);

	SetEnabled(true);
	SetVisible(true);

	ElementProc(m_Hwnd, WM_CREATE, 0, 0);
	UpdateWindow(m_Hwnd);

	return true;
}