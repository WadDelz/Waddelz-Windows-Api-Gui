#include "CustomItem.h"

using namespace gui;

START_ELEMENT_SUBPROC_NOSWITCH(CustomItem)
END_PROC_NOSWITCH(CALL_DEF_SUBPROC())

CustomItem::CustomItem()
{
	SetClassname("CustomItem");
}

CustomItem::CustomItem(Element* parent, const char* wndclassname, int command)
{
	SetClassname("CustomItem");
	MakeItem(parent, wndclassname, nullptr, 0, 0, 0, 0, command, false);

	if (parent)
		parent->AddChild(this);
}

CustomItem::CustomItem(Element* parent, const char* wndclassname, const char* text, int flags, int x, int y, int w, int h, int command, bool bUseSubproc, const char* classname)
{
	SetClassname(classname);
	MakeItem(parent, wndclassname, text, flags, x, y, w, h, command, bUseSubproc);

	if (parent)
		parent->AddChild(this);
}

bool CustomItem::MakeItem(Element* parent, const char* wndclassname, const char* text, int flags, int x, int y, int w, int h, int command, bool bUseSubproc)
{
	m_iCommandId = command;

	m_Hwnd = CreateWindow(
		wndclassname,
		text,
		flags,
		x, y,
		w, h,
		(parent) ? parent->GetHandle() : nullptr,
		(HMENU)command,
		GetModuleHandle(nullptr),
		nullptr
	);

	if (!m_Hwnd)
		return false;

	SetVisible(true);
	SetEnabled(true);

	SET_ELEMENT_USERDATA(m_Hwnd, this);
	if (bUseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}

	return true;
}

bool gui::RegisterCustomItem(
	LPCSTR classname,
	WNDPROC wndproc,
	HINSTANCE instance,
	HICON icon,
	HBRUSH hbrbackground,
	HCURSOR cursor,
	INT style,
	LPCSTR menuname
)
{
	WNDCLASS wc = {};
	wc.lpszClassName = classname;
	wc.lpfnWndProc = wndproc;
	wc.style = style;
	wc.lpszMenuName = menuname;
	wc.hbrBackground = hbrbackground;
	wc.hInstance = instance;
	wc.hIcon = icon;
	wc.hCursor = cursor;

	return RegisterClass(&wc);
}
