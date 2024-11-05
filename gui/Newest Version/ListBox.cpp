#include "ListBox.h"

using namespace gui;

START_ELEMENT_SUBPROC(ListBox)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CallWindowProc(m_DefaultProc, hwnd, msg, wp, lp))

ListBox::ListBox() : BaseClass()
{
	SetClassname("ListBox");
}

ListBox::ListBox(Element* parent, const int& command) : BaseClass()
{
	SetClassname("ListBox");
	MakeListBox(parent, 0, 0, 0, 0, DEF_FLAGS_LISTBOX, command, false);
	parent->AddChild(this);
}

ListBox::ListBox(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const bool& bUseSubproc, const int& command, const char* classname)
{
	SetClassname(classname);
	MakeListBox(parent, x, y, w, h, flags, command, bUseSubproc);
	parent->AddChild(this);
}

bool ListBox::MakeListBox(Element* parent, int x, int y, int w, int h, long flags, int command, bool UseSubproc)
{
	if (!parent)
		return false;

	m_Hwnd = CreateWindow(
		"LISTBOX",
		nullptr,
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

void ListBox::AddItem(const char* item)
{
	SendMessage(m_Hwnd, LB_ADDSTRING, 0, (LPARAM)item);
}

void ListBox::RemoveItem(int index)
{
	SendMessage(m_Hwnd, LB_DELETESTRING, (WPARAM)index, 0);
}

void ListBox::ClearItems()
{
	SendMessage(m_Hwnd, LB_RESETCONTENT, 0, 0);
}

void ListBox::SetSelectedIndex(int index)
{
	SendMessage(m_Hwnd, LB_SETCURSEL, (WPARAM)index, 0);
}

int ListBox::GetSelectedIndex()
{
	return SendMessage(m_Hwnd, LB_GETCURSEL, 0, 0);
}

int ListBox::GetNumItems()
{
	LRESULT itemCount = SendMessage(m_Hwnd, LB_GETCOUNT, 0, 0);
	return (itemCount == LB_ERR) ? 0 : (int)itemCount;
}

void ListBox::GetItemArray(char** arr)
{
	int itemCount = GetNumItems();
	if (itemCount == 0 || !arr)
		return;

	for (int i = 0; i < itemCount; ++i)
	{
		int textLength = SendMessage(m_Hwnd, LB_GETTEXTLEN, i, 0);

		if (textLength != LB_ERR)
		{
			arr[i] = new char[textLength + 1];
			SendMessage(m_Hwnd, LB_GETTEXT, i, (LPARAM)arr[i]);
		}
	}
}

int ListBox::GetIndexFromString(const char* item)
{
	return SendMessage(m_Hwnd, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)item);
}

int ListBox::GetItemTextLength(int index)
{
	return SendMessage(m_Hwnd, LB_GETTEXTLEN, index, 0);
}
