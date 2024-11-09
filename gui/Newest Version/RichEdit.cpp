#include "RichEdit.h"
#include <Richedit.h>

using namespace gui;

START_ELEMENT_SUBPROC(RichEdit)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_PROC(CALL_DEF_SUBPROC())

HINSTANCE RichEdit::g_RichEditLibrary = nullptr;
HFONT RichEdit::m_DefaultFont = nullptr;

RichEdit::RichEdit() : BaseClass()
{
	SetClassname("RichEdit");
}

RichEdit::RichEdit(Element* parent, const char* text, const int& command) : BaseClass()
{
	SetClassname("RichEdit");
	MakeRichEdit(parent, text, 0, 0, 0, 0, DEF_FLAGS_RICHEDIT, command);
	parent->AddChild(this);
}

RichEdit::RichEdit(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* text, const char* classname) : BaseClass()
{
	SetClassname(classname);
	MakeRichEdit(parent, text, x, y, w, h, flags, command, bUseSubproc);
	parent->AddChild(this);
}

void RichEdit::AppendText(const char* text)
{
	CHARRANGE cr;
	cr.cpMin = -1;
	cr.cpMax = -1;

	SendMessage(m_Hwnd, EM_EXSETSEL, 0, (LPARAM)&cr);
	SendMessage(m_Hwnd, EM_REPLACESEL, FALSE, (LPARAM)text);
}

void RichEdit::SetSelected(int start, int end)
{
	SendMessage(m_Hwnd, EM_SETSEL, start, end);
}

void RichEdit::SetSelectedTextColor(COLORREF color)
{
	CHARFORMAT2 cf;
	ZeroMemory(&cf, sizeof(cf));
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = color;

	SendMessage(m_Hwnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void RichEdit::ReplaceSelectedText(const char* text, BOOL CaretMoveToEnd)
{
	SendMessage(m_Hwnd, EM_REPLACESEL, !CaretMoveToEnd, (LPARAM)text);
}

void RichEdit::SetFont(HFONT hFont)
{
	CHARFORMAT2 cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT2));
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_WEIGHT;

	LOGFONT lf;
	GetObject(hFont, sizeof(LOGFONT), &lf);

	//this works so i aint changing it
	if (hFont != m_DefaultFont)
		cf.yHeight = lf.lfHeight * 20;
	else
		cf.yHeight = lf.lfHeight * 30;

	cf.wWeight = (WORD)lf.lfWeight;
	cf.bCharSet = lf.lfCharSet;
	lstrcpy(cf.szFaceName, lf.lfFaceName);

	int textLength = GetTextLength();
	SendMessage(m_Hwnd, EM_SETSEL, textLength, textLength);
	SendMessage(m_Hwnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void RichEdit::SetTextColor(COLORREF color)
{
	CHARFORMAT2 cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT2));
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = color;

	int textLength = GetTextLength();
	SendMessage(m_Hwnd, EM_SETSEL, textLength, textLength);
	SendMessage(m_Hwnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void RichEdit::SetTextBackgroundColor(COLORREF color)
{
	CHARFORMAT2 cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT2));
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_BACKCOLOR;
	cf.crBackColor = color;

	int textLength = GetTextLength();
	SendMessage(m_Hwnd, EM_SETSEL, textLength, textLength);
	SendMessage(m_Hwnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void RichEdit::SetBackgroundColor(COLORREF color)
{
	SendMessage(m_Hwnd, EM_SETBKGNDCOLOR, 0, color);
}

void RichEdit::SetTextSize(int size)
{
	CHARFORMAT2 cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT2));
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_SIZE;
	cf.yHeight = size * 20;

	int textLength = GetTextLength();
	SendMessage(m_Hwnd, EM_SETSEL, textLength, textLength);
	SendMessage(m_Hwnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

HFONT RichEdit::GetDefaultFont()
{
	return m_DefaultFont;
}

void RichEdit::OnDeconstructor()
{
	DeleteThis();
}

int RichEdit::GetTextLength()
{
	return GetWindowTextLength(m_Hwnd);
}

void RichEdit::ClearText()
{
	SetText("");
}

void RichEdit::Init()
{
	g_RichEditLibrary = LoadLibrary("Msftedit.dll");
}

void RichEdit::Shutdown()
{
	if (g_RichEditLibrary)
		FreeLibrary(g_RichEditLibrary);

	g_RichEditLibrary = nullptr;
}

bool RichEdit::MakeRichEdit(Element* parent, const char* text, int x, int y, int w, int h, long flags, int command, bool UseSubproc)
{
	m_iCommandId = command;

	if (!parent)
		return false;

	m_Hwnd = CreateWindow(
		"RICHEDIT50W",
		text,
		flags,
		x, y,
		w, h,
		parent->GetHandle(),
		(HMENU)command,
		GetModuleHandle(nullptr),
		nullptr
	);

	if (!m_DefaultFont)
		m_DefaultFont = GetDefaultFontBase();

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

HFONT RichEdit::GetDefaultFontBase()
{
	CHARFORMAT2 cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT2));
	cf.cbSize = sizeof(CHARFORMAT2);

	if (SendMessage(m_Hwnd, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)&cf))
	{
		LOGFONT lf;
		ZeroMemory(&lf, sizeof(LOGFONT));
		lf.lfHeight = cf.yHeight / -20;
		lf.lfWeight = cf.wWeight;
		lf.lfCharSet = cf.bCharSet;
		lstrcpy(lf.lfFaceName, cf.szFaceName);

		return CreateFontIndirect(&lf);
	}

	return NULL;
}
