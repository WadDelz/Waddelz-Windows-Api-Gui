#include "CustomItem.h"

using namespace gui;

START_ELEMENT_SUBPROC_NOSWITCH(CustomItem)
END_ELEMENT_PROC_NO_SWITCH(CALL_DEF_SUBPROC())

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

void CustomItem::MakeItem(Element* parent, const char* wndclassname, const char* text, int flags, int x, int y, int w, int h, int command, bool bUseSubproc)
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

	SetVisible(true);
	SetEnabled(true);

	SET_ELEMENT_USERDATA(m_Hwnd, this);
	if (bUseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}
}

bool gui::RegisterCustomItem(const char* classname, WNDPROC wndproc, HBRUSH hbrbackground, HINSTANCE instance, HICON icon, HCURSOR cursor)
{
	WNDCLASS wc = {};
	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.lpfnWndProc = wndproc;
	wc.hInstance = instance;

	return RegisterClass(&wc);
}
