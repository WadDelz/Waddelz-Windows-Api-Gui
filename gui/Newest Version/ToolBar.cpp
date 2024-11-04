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

bool ToolBar::IsButtonChecked(int command)
{
	LRESULT state = SendMessage(m_Hwnd, TB_GETSTATE, (WPARAM)command, 0);
	return (state & TBSTATE_CHECKED) != 0;
}

void ToolBar::SetButtonChecked(int command, bool checked)
{
	SendMessage(m_Hwnd, TB_SETSTATE, (WPARAM)command, (LPARAM)(checked ? TBSTATE_CHECKED : 0));
}

bool ToolBar::IsStateEnabled(int command, int state)
{
	LRESULT lstate = SendMessage(m_Hwnd, TB_GETSTATE, (WPARAM)command, 0);
	return (lstate & state) != 0;
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