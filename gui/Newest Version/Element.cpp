#include "Element.h"
#include "PropertyPage.h"
#include "ToolTip.h"

using namespace gui;

Element::Element()
{
	m_Hwnd = nullptr;
	m_Parent = nullptr;
	m_szName = nullptr;
	m_szClassName = nullptr;
	m_PropertyPage = nullptr;
	m_bVisible = true;
	m_bEnabled = true;
	bDeleteThisHack = false;
	m_Children = {};
	m_iCommandId = 0;
}

void Element::SetName(const char* name)
{
	if (m_szName)
		free(m_szName);

	m_szName = _strdup(name);
}

void Element::GetPos(int& x, int& y)
{
	x = y = 0;

	if (!m_Hwnd)
		return;

	RECT rect = {};
	GetWindowRect(m_Hwnd, &rect);

	x = rect.left;
	y = rect.top;
}

int Element::GetX()
{
	int x, y;
	GetPos(x, y);
	return x;
}

int Element::GetY()
{
	int x, y;
	GetPos(x, y);
	return y;
}

int Element::GetWide()
{
	int wide, tall;
	GetSize(wide, tall);
	return wide;
}

int Element::GetTall()
{
	int wide, tall;
	GetSize(wide, tall);
	return tall;
}

void Element::GetSize(int& wide, int& tall)
{
	wide = tall = 0;

	if (!m_Hwnd)
		return;

	RECT rect = {};
	GetWindowRect(m_Hwnd, &rect);

	wide = rect.right - rect.left;
	tall = rect.bottom - rect.top;
}

void Element::GetBounds(int& x, int& y, int& wide, int& tall)
{
	GetPos(x, y);
	GetSize(wide, tall);
}

void Element::SetPos(const int& x, const int& y)
{
	SetWindowPos(m_Hwnd, nullptr, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void Element::SetX(const int& x)
{
	SetWindowPos(m_Hwnd, nullptr, x, GetY(), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void Element::SetY(const int& y)
{
	SetWindowPos(m_Hwnd, nullptr, GetX(), y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void Element::SetWide(const int& wide)
{
	SetWindowPos(m_Hwnd, nullptr, 0, 0, wide, GetTall(), SWP_NOZORDER | SWP_NOMOVE);
}

void Element::SetTall(const int& tall)
{
	SetWindowPos(m_Hwnd, nullptr, 0, 0, GetWide(), tall, SWP_NOZORDER | SWP_NOMOVE);
}

void Element::SetSize(const int& wide, const int& tall)
{
	SetWindowPos(m_Hwnd, nullptr, 0, 0, wide, tall, SWP_NOZORDER | SWP_NOMOVE);
}

void Element::SetBounds(const int& x, const int& y, const int& wide, const int& tall)
{
	SetWindowPos(m_Hwnd, nullptr, x, y, wide, tall, SWP_NOZORDER);
}

void Element::SetIcon(HICON icon, bool big)
{
	SendMessage(m_Hwnd, WM_SETICON, big ? ICON_BIG : ICON_SMALL, (LPARAM)icon);
}

void Element::OnDeconstructor() { DeleteThis(); }
void Element::OnFileSelected(int id, const char* file, FileDialogType type) {}

void Element::SetPropertyPage(PropertyPage* page)
{
	m_PropertyPage = page;
}

PropertyPage* Element::GetPropertyPage()
{
	return m_PropertyPage;
}

const char* Element::GetName()
{
	return m_szName;
}

const char* Element::GetClassname()
{
	return m_szClassName;
}

Element* Element::GetParent()
{
	return m_Parent;
}

bool Element::IsVisible()
{
	return m_bVisible;
}

void Element::SetVisible(const bool& visible)
{
	ShowWindow(m_Hwnd, (visible) ? SW_SHOW : SW_HIDE);
	m_bVisible = visible;
}

bool Element::IsEnabled()
{
	return m_bEnabled;
}

void Element::SetEnabled(const bool& enabled)
{
	EnableWindow(m_Hwnd, enabled);
	m_bEnabled = enabled;
}

void Element::AddChild(Element* child)
{
	if (std::find(m_Children.begin(), m_Children.end(), child) == m_Children.end())
		m_Children.push_back(child);

	child->SetParent(this);
}

void Element::DeleteChild(Element* child)
{
	auto find = std::find(m_Children.begin(), m_Children.end(), child);
	if (find != m_Children.end())
	{
		m_Children.erase(find);
		child->DeleteThis();
	}
}

void Element::RemoveChild(Element* child)
{
	auto find = std::find(m_Children.begin(), m_Children.end(), child);
	if (find != m_Children.end())
		m_Children.erase(find);
}

void Element::SetParent(Element* parent)
{
	m_Parent = parent;
}

void Element::DeleteThis()
{
	if (bDeleteThisHack)
		return;

	if (m_Hwnd)
		DestroyWindow(m_Hwnd);

	if (m_Parent)
		m_Parent->RemoveChild(this);

	if (m_PropertyPage)
		m_PropertyPage->RemoveElement(this, false);

	for (unsigned int i = 0; i < m_Children.size(); i++)
	{
		Element* curr = m_Children[i];
		if (!curr)
			continue;

		delete  curr;
	}

	if (m_szName)
		free(m_szName);
	
	if (m_szClassName)
		free(m_szClassName);
}

int Element::GetCommand()
{
	return m_iCommandId;
}

unsigned int Element::GetFlags()
{
	return GET_ELEMENT_FLAGS(m_Hwnd);
}

void Element::SetFlags(unsigned int flags)
{
	SET_ELEMENT_FLAGS(m_Hwnd, flags);
}

unsigned int Element::GetExtendedFlags()
{
	return GET_ELEMENT_EX_FLAGS(m_Hwnd);
}

void Element::SetExtendedFlags(unsigned int flags)
{
	SET_ELEMENT_EX_FLAGS(m_Hwnd, flags);
}

void Element::SetText(const char* text)
{
	SetWindowText(m_Hwnd, text);
}

void Element::GetText(char* buf, int len)
{
	GetWindowText(m_Hwnd, buf, len);
}

void Element::SetSubproc(WNDPROC proc)
{
	m_DefaultProc = (WNDPROC)(GetWindowLongPtr(m_Hwnd, GWLP_WNDPROC));
	SetWindowLongPtr(m_Hwnd, GWLP_WNDPROC, (LONG)proc);
}

void Element::SetFocusToThis()
{
	SetFocus(m_Hwnd);
}

HWND Element::GetHandle()
{
	return m_Hwnd;
}

POINT Element::ClientFromScreen(POINT pt)
{
	POINT ret = { 0,0 };

	if (!m_Hwnd)
		return ret;

	ret = pt;
	ScreenToClient(m_Hwnd, &ret);
	return ret;
}

POINT Element::ClientFromScreen(Element* element, POINT pt)
{
	POINT ret = { 0,0 };

	if (!element)
		return ret;

	if (!element->m_Hwnd)
		return ret;

	ret = pt;
	ScreenToClient(m_Hwnd, &ret);
	return ret;
}

void Element::Redraw(bool repaint, Element* item, const RECT* rect)
{
	HWND hwnd = item ? item->m_Hwnd : m_Hwnd;
	InvalidateRect(hwnd, rect, repaint);
	UpdateWindow(hwnd);
}

std::vector<Element*> Element::GetChildren()
{
	return m_Children;
}

std::vector<ToolTip*> Element::GetToolTips()
{
	return m_ToolTips;
}

int Element::EmptyMessageBox(int flags, const char* title, const char* text, ...)
{
	char buf[2048] = { 0 };

	if (text)
	{
		va_list list;
		va_start(list, text);
		vsnprintf_s(buf, sizeof(buf), text, list);
		va_end(list);
	}

	return MessageBox(nullptr, buf, title, flags);
}

int Element::ShowMessageBox(int flags, const char* title, const char* text, ...)
{
	char buf[2048] = { 0 };

	if (text)
	{
		va_list list;
		va_start(list, text);
		vsnprintf_s(buf, sizeof(buf), text, list);
		va_end(list);
	}

	return MessageBox(m_Hwnd, buf, title, flags);
}

//void Element::MoveToFront()
//{
//	SetWindowPos(m_Hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//	SetWindowPos(m_Hwnd, HWND_TOP, 0, 0, 0, 0,  SWP_NOMOVE | SWP_NOSIZE);
//	SetWindowPos(m_Hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//}

Element::~Element()
{
	//OnDeconstructor();
}

void Element::SetClassname(const char* classname)
{
	if (m_szClassName)
		free(m_szClassName);

	m_szClassName = _strdup(classname);
}

void Element::AddToolTip(ToolTip* tip)
{
	if (std::find(m_ToolTips.begin(), m_ToolTips.end(), tip) == m_ToolTips.end())
		m_ToolTips.push_back(tip);
}

void Element::DeleteToolTip(ToolTip* tip)
{
	delete tip;
}

void Element::RemoveToolTip(ToolTip* tip)
{
	auto find = std::find(m_ToolTips.begin(), m_ToolTips.end(), tip);
	if (find != m_ToolTips.end())
		m_ToolTips.erase(find);
}

Element* gui::GetElementFromPoint(POINT pt)
{
	HWND hwnd = WindowFromPoint(pt);
	if (!hwnd)
		return nullptr;

	return (Element*)GET_ELEMENT_USERDATA(hwnd);
}

Element* gui::GetElementFromHwnd(HWND hwnd)
{
	return (Element*)GET_ELEMENT_USERDATA(hwnd);
}

Element* gui::GetElementFocus()
{
	HWND hwnd = GetFocus();
	if (!hwnd)
		return nullptr;

	return (Element*)GET_ELEMENT_USERDATA(hwnd);
}
