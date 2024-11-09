#include "ComboBox.h"

using namespace gui;

START_ELEMENT_SUBPROC(ComboBox)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_PROC(CALL_DEF_SUBPROC())

ComboBox::ComboBox() : BaseClass()
{
	m_ElementHeight = 0;
	SetClassname("ComboBox");
}

ComboBox::ComboBox(Element* parent, const int& command) : BaseClass()
{
	m_ElementHeight = 0;
	SetClassname("ComboBox");
	MakeComboBox(parent, 0, 0, 0, 0, 0, DEF_FLAGS_COMBOBOX, command, false);
	parent->AddChild(this);
}

ComboBox::ComboBox(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& dropdownheight, const int& flags, const int& command, bool bUseSubproc, const char* classname) : BaseClass()
{
	m_ElementHeight = 0;
	SetClassname(classname);
	MakeComboBox(parent, x, y, w, h, dropdownheight, flags, command, bUseSubproc);
	parent->AddChild(this);
}

void ComboBox::SelectItem(int index)
{
	SendMessage(m_Hwnd, CB_SETCURSEL, index, 0);
}

void ComboBox::SelectItem(const char* text)
{
	int index = SendMessage(m_Hwnd, CB_FINDSTRINGEXACT, -1, (LPARAM)text);
	if (index != CB_ERR)
		SendMessage(m_Hwnd, CB_SETCURSEL, index, 0);
}

void ComboBox::AddItem(const char* text)
{
	SendMessage(m_Hwnd, CB_ADDSTRING, 0, (LPARAM)text);
}

int ComboBox::GetCurrentSelected()
{
	return SendMessage(m_Hwnd, CB_GETCURSEL, 0, 0);
}

int ComboBox::GetCount()
{
	return SendMessage(m_Hwnd, CB_GETCOUNT, 0, 0);
}

void ComboBox::DeleteAllItems()
{
	SendMessage(m_Hwnd, CB_RESETCONTENT, 0, 0);
}

void ComboBox::DeleteItem(int index)
{
	SendMessage(m_Hwnd, CB_DELETESTRING, index, 0);
}

void ComboBox::DeleteItem(const char* str)
{
	int index = SendMessage(m_Hwnd, CB_FINDSTRINGEXACT, -1, (LPARAM)str);
	if (index != CB_ERR)
		SendMessage(m_Hwnd, CB_DELETESTRING, index, 0);
}

void ComboBox::SetElementHeight(const int& height)
{
	SendMessage(m_Hwnd, CB_SETITEMHEIGHT, -1, (LPARAM)height);
	m_ElementHeight = height;
}

int ComboBox::GetElementHeight()
{
	return m_ElementHeight;
}

bool ComboBox::MakeComboBox(Element* parent, int x, int y, int w, int h, int dropdownheight, long flags, int command, bool UseSubproc)
{
	m_iCommandId = command;

	if (!parent)
		return false;

	m_Hwnd = CreateWindow(
		"ComboBox",
		"",
		flags,
		x, y,
		w, dropdownheight,
		parent->GetHandle(),
		(HMENU)command,
		GetModuleHandle(nullptr),
		nullptr
	);

	SendMessage(m_Hwnd, CB_SETITEMHEIGHT, -1, (LPARAM)h);
	m_ElementHeight = h;

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