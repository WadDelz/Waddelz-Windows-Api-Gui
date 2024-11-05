#include "Label.h"

using namespace gui;

START_ELEMENT_SUBPROC(Label)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CallWindowProc(m_DefaultProc, hwnd, msg, wp, lp))

Label::Label() : BaseClass()
{
	SetClassname("Label");
}

Label::Label(Element* parent, const char* text, const int& command) : BaseClass()
{
	SetClassname("Label");
	MakeLabel(parent, text, 0, 0, 0, 0, DEF_FLAGS_LABEL, command, false);
	parent->AddChild(this);
}

Label::Label(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* text, const char* classname)
{
	SetClassname(classname);
	MakeLabel(parent, text, x, y, w, h, flags, command, bUseSubproc);
	parent->AddChild(this);
}

void Label::SetFont(HFONT font, BOOL bRedraw)
{
	SendMessage(m_Hwnd, WM_SETFONT, (WPARAM)font, bRedraw);
}

HFONT Label::GetFont()
{
	return (HFONT)SendMessage(m_Hwnd, WM_GETFONT, 0, 0);
}

bool Label::MakeLabel(Element* parent, const char* text, int x, int y, int w, int h, long flags, int command, bool UseSubproc)
{
	m_iCommandId = command;

	if (!parent)
		return false;

	m_Hwnd = CreateWindow(
		"STATIC",
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

	SET_ELEMENT_USERDATA(m_Hwnd, this);
	if (UseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}

	return true;
}