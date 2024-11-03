#include "Checkbutton.h"

using namespace gui;

START_ELEMENT_SUBPROC(CheckButton)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

CheckButton::CheckButton() : BaseClass()
{
	SetClassname("CheckButton");
}

CheckButton::CheckButton(Element* parent, const char* text, const int& command) : BaseClass()
{
	SetClassname("CheckButton");
	MakeCheckbutton(parent, text, 0, 0, 0, 0, DEF_FLAGS_CHECKBUTTON, command, false, false);
	parent->AddChild(this);
}

CheckButton::CheckButton(Element* parent, const char* text, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bChecked, bool bUseSubproc, const char* classname)
{
	SetClassname(classname);
	MakeCheckbutton(parent, text, x, y, w, h, flags, command, bChecked, bUseSubproc);
	parent->AddChild(this);
}

bool CheckButton::IsChecked()
{
	return SendMessage(m_Hwnd, BM_GETCHECK, 0, 0);
}

void CheckButton::SetChecked(const bool& bChecked)
{
	SendMessage(m_Hwnd, BM_SETCHECK, (bChecked) ? BST_CHECKED : BST_UNCHECKED, 0);
}

void CheckButton::OnDeconstructor()
{
	DeleteThis();
}

bool CheckButton::MakeCheckbutton(Element* parent, const char* text, int x, int y, int w, int h, long flags, int command, bool bChecked, bool UseSubproc)
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

	if (bChecked)
		SendMessage(m_Hwnd, BM_SETCHECK, BST_CHECKED, 0);

	SET_ELEMENT_USERDATE(m_Hwnd, this);
	if (UseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}

	return true;
}
