#include "ToolBar.h"

using namespace gui;

ToolBar::ToolBar()
{
	m_Hwnd = nullptr;
	m_ImageList = nullptr;
	m_Parent = nullptr;
}

ToolBar::ToolBar(Element* parent, ImageList* il, int flags)
{
	m_Parent = parent;
	m_ImageList = il;
	m_Hwnd = nullptr;
	MakeToolBar(parent, flags, il);
}

void ToolBar::AddButton(int command, int state, int style, int ibitmap)
{
	TBBUTTON button[1] = {};
	button[0].idCommand = command;
	button[0].fsState = state;
	button[0].fsStyle = style;
	button[0].iBitmap = ibitmap;

	SendMessage(m_Hwnd, TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&button);
}

void ToolBar::SetImageList(ImageList* imagelist, bool bDeleteOld)
{
	if (bDeleteOld && m_ImageList)
	{
		m_ImageList->DeleteImageList();
		delete m_ImageList;
	}

	m_ImageList = imagelist;
	SendMessage(m_Hwnd, TB_SETIMAGELIST, 0, (LPARAM)imagelist->GetImageList());
}

ImageList* ToolBar::GetImageList()
{
	return m_ImageList;
}

bool ToolBar::IsButtonEnabled(int command)
{
	LRESULT state = SendMessage(m_Hwnd, TB_GETSTATE, (WPARAM)command, 0);
	return (state & TBSTATE_ENABLED) != 0;
}

void ToolBar::EnableButton(int command, bool enable)
{
	SendMessage(m_Hwnd, TB_SETSTATE, (WPARAM)command, (LPARAM)(enable ? TBSTATE_ENABLED : 0));
}

bool ToolBar::IsStateEnabled(int command, int state)
{
	LRESULT lstate = SendMessage(m_Hwnd, TB_GETSTATE, (WPARAM)command, 0);
	return (lstate & state) != 0;
}

void ToolBar::SetButtonImageIndex(int command, int index)
{
	TBBUTTONINFO buttonInfo = {};
	buttonInfo.cbSize = sizeof(TBBUTTONINFO);
	buttonInfo.dwMask = TBIF_IMAGE;
	buttonInfo.iImage = index;

	SendMessage(m_Hwnd, TB_SETBUTTONINFO, (WPARAM)command, (LPARAM)&buttonInfo);
}

int ToolBar::GetButtonIconIndex(int command)
{
	TBBUTTONINFO buttonInfo = {};
	buttonInfo.cbSize = sizeof(TBBUTTONINFO);
	buttonInfo.dwMask = TBIF_IMAGE;

	if (SendMessage(m_Hwnd, TB_GETBUTTONINFO, (WPARAM)command, (LPARAM)&buttonInfo) != -1)
		return buttonInfo.iImage;

	return -1;
}

bool ToolBar::IsButtonPressedDown(int command)
{
	LRESULT state = SendMessage(m_Hwnd, TB_GETSTATE, (WPARAM)command, 0);
	return (state & TBSTATE_CHECKED) != 0;
}

void ToolBar::SetButtonPressedDown(int command, bool checked)
{
	DWORD state = TBSTATE_ENABLED;
	if (checked)
		state |= TBSTATE_CHECKED;

	SendMessage(m_Hwnd, TB_SETSTATE, (WPARAM)command, (LPARAM)state);
}

void ToolBar::SetX(int x)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	SetWindowPos(m_Hwnd, nullptr, x, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void ToolBar::SetY(int y)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	SetWindowPos(m_Hwnd, nullptr, rect.left, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void ToolBar::SetWidth(int width)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	SetWindowPos(m_Hwnd, nullptr, rect.left, rect.top, width, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
}

void ToolBar::SetTall(int height)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	SetWindowPos(m_Hwnd, nullptr, rect.left, rect.top, rect.right - rect.left, height, SWP_NOZORDER | SWP_NOMOVE);
}

void ToolBar::SetPos(int x, int y)
{
	SetWindowPos(m_Hwnd, nullptr, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void ToolBar::SetSize(int width, int height)
{
	SetWindowPos(m_Hwnd, nullptr, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
}

void ToolBar::SetBounds(int x, int y, int width, int height)
{
	SetWindowPos(m_Hwnd, nullptr, x, y, width, height, SWP_NOZORDER);
}

void ToolBar::GetX(int* x)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	if (x) *x = rect.left;
}

void ToolBar::GetY(int* y)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	if (y) *y = rect.top;
}

void ToolBar::GetWidth(int* width)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	if (width) *width = rect.right - rect.left;
}

void ToolBar::GetTall(int* height)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	if (height) *height = rect.bottom - rect.top;
}

void ToolBar::GetPos(int* x, int* y)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	if (x) *x = rect.left;
	if (y) *y = rect.top;
}

void ToolBar::GetSize(int* width, int* height)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);
	if (width) *width = rect.right - rect.left;
	if (height) *height = rect.bottom - rect.top;
}

void ToolBar::GetBounds(int* x, int* y, int* width, int* height)
{
	RECT rect;
	GetWindowRect(m_Hwnd, &rect);

	if (x) *x = rect.left;
	if (y) *y = rect.top;
	if (width) *width = rect.right - rect.left;
	if (height) *height = rect.bottom - rect.top;
}

static bool bDidInitCommonCtrls = false;

bool ToolBar::MakeToolBar(Element* parent, int flags, ImageList* il)
{
	if (!parent)
		return false;

	parent->SetToolBar(this);

	if (!bDidInitCommonCtrls)
	{
		INITCOMMONCONTROLSEX icex = {};
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_BAR_CLASSES;
		InitCommonControlsEx(&icex);
	}
	
	m_Hwnd = CreateWindow(
		TOOLBARCLASSNAME,
		"",
		WS_CHILD | WS_VISIBLE | TBSTYLE_WRAPABLE,
		0, 0, 
		0, 0,
		parent->GetHandle(), 
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	SendMessage(m_Hwnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	if (il)
		SendMessage(m_Hwnd, TB_SETIMAGELIST, 0, (LPARAM)il->GetImageList());

	return true;
}