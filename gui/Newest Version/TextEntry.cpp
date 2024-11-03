#include "TextEntry.h"

using namespace gui;

START_ELEMENT_SUBPROC(TextEntry)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

TextEntry::TextEntry() : BaseClass()
{
	SetClassname("TextEntry");
}

TextEntry::TextEntry(Element* parent, const char* text, const int& command) : BaseClass()
{
	SetClassname("TextEntry");
	MakeTextEntry(parent, text, 0, 0, 0, 0, DEF_FLAGS_TEXTENTRY, command);
	parent->AddChild(this);
}

TextEntry::TextEntry(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* text, const char* classname) : BaseClass()
{
	SetClassname(classname);
	MakeTextEntry(parent, text, x, y, w, h, flags, command, bUseSubproc);
	parent->AddChild(this);
}

void TextEntry::SetSelected(int start, int end)
{
	SendMessage(m_Hwnd, EM_SETSEL, start, end);
}

void TextEntry::ReplaceSelectedText(const char* text, BOOL CaretMoveToEnd)
{
	SendMessage(m_Hwnd, EM_REPLACESEL, !CaretMoveToEnd, (LPARAM)text);
}

void TextEntry::AppendText(const char* text)
{
	int len = GetTextLength();
	SetSelected(len, len);
	ReplaceSelectedText(text, TRUE);
}

void TextEntry::OnDeconstructor()
{
	DeleteThis();
}

int TextEntry::GetTextLength()
{
	return GetWindowTextLength(m_Hwnd);
}

void TextEntry::ClearText()
{
	SetText("");
}

bool TextEntry::MakeTextEntry(Element* parent, const char* text, int x, int y, int w, int h, long flags, int command, bool UseSubproc)
{
	m_iCommandId = command;

	if (!parent)
		return false;

	m_Hwnd = CreateWindow(
		"EDIT",
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