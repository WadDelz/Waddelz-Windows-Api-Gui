#include "Button.h"

using namespace gui;

START_ELEMENT_SUBPROC(Button)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CallWindowProc(m_DefaultProc, hwnd, msg, wp, lp))

Button::Button() : BaseClass()
{
	SetClassname("Button");
}

Button::Button(Element* parent, const char* text, const int& command) : BaseClass()
{
	SetClassname("Button");
	MakeButton(parent, text, 0, 0, 0, 0, DEF_FLAGS_BUTTON, command, false);
	parent->AddChild(this);
}

Button::Button(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* text, const char* classname)
{
	SetClassname(classname);
	MakeButton(parent, text, x, y, w, h, flags, command, bUseSubproc);
	parent->AddChild(this);
}

void Button::OnDeconstructor()
{
	DeleteThis();
}

bool Button::MakeButton(Element* parent, const char* text, int x, int y, int w, int h, long flags, int command, bool UseSubproc)
{
	m_iCommandId = command;

	if (!parent)
		return false;

	m_Hwnd = CreateWindow(
		"BUTTON",
		text,
		flags,
		x, y,
		w, h,
		parent->GetHandle(),
		(HMENU)command,
		GetModuleHandle(nullptr),
		nullptr
	);

	SetVisible(true);
	SetEnabled(true);

	SET_ELEMENT_USERDATE(m_Hwnd, this);
	if (UseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}

	return true;
}