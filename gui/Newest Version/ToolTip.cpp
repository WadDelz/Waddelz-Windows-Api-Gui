#include "ToolTip.h"

using namespace gui;

ToolTip::ToolTip() 
{
    m_Elements = {};
    m_parent = nullptr;
}

ToolTip::ToolTip(Element* parent, int flags, int maxwidth)
{
    m_Elements = {};
	m_parent = parent;
	MakeToolTip(flags, maxwidth);
}

void ToolTip::AddTool(Element* toolelement, const char* text)
{
    if (!toolelement)
        return;

    TOOLINFO toolInfo = {};
    toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.uFlags = TTF_SUBCLASS;
    toolInfo.hwnd = toolelement->GetHandle();
    toolInfo.lpszText = (LPSTR)text;

    RECT rect;
    GetClientRect(toolelement->GetHandle(), &rect);
    toolInfo.rect = rect;

    SendMessage(m_Hwnd, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);

    auto it = std::find(m_Elements.begin(), m_Elements.end(), toolelement);
    if (it == m_Elements.end())
        m_Elements.push_back(toolelement);
}

void ToolTip::AddTool(HWND toolhwnd, const char* text)
{
    TOOLINFO toolInfo = {};
    toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.uFlags = TTF_SUBCLASS;
    toolInfo.hwnd = toolhwnd;
    toolInfo.lpszText = (LPSTR)text;

    RECT rect;
    GetClientRect(toolhwnd, &rect);
    toolInfo.rect = rect;

    SendMessage(m_Hwnd, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);

    Element* element = GetElementFromHwnd(toolhwnd);
    if (!element)
        return;

    auto it = std::find(m_Elements.begin(), m_Elements.end(), element);
    if (it == m_Elements.end())
        m_Elements.push_back(element);
}

void ToolTip::RemoveTool(HWND hwnd)
{
	TOOLINFO toolInfo = {};
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = hwnd;

	SendMessage(m_Hwnd, TTM_DELTOOL, 0, (LPARAM)&toolInfo);

    Element * element = GetElementFromHwnd(hwnd);
    if (!element)
        return;

    auto it = std::find(m_Elements.begin(), m_Elements.end(), element);
    if (it != m_Elements.end())
        m_Elements.erase(it);
}

void ToolTip::RemoveTool(Element* element)
{
	if (!element)
		return;

	TOOLINFO toolInfo = {};
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = element->GetHandle();

	SendMessage(m_Hwnd, TTM_DELTOOL, 0, (LPARAM)&toolInfo);

    auto it = std::find(m_Elements.begin(), m_Elements.end(), element);
    if (it != m_Elements.end())
        m_Elements.erase(it);
}

void ToolTip::UpdateToolText(Element* toolelement, const char* text)
{
    if (!toolelement)
        return;

    TOOLINFO toolInfo = {};
    toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.hwnd = toolelement->GetHandle();
    toolInfo.lpszText = (LPSTR)text;

    SendMessage(m_Hwnd, TTM_UPDATETIPTEXT, 0, (LPARAM)&toolInfo);
}

void ToolTip::UpdateToolText(HWND toolHwnd, const char* text)
{
    TOOLINFO toolInfo = {};
    toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.hwnd = toolHwnd;
    toolInfo.lpszText = (LPSTR)text;

    SendMessage(m_Hwnd, TTM_UPDATETIPTEXT, 0, (LPARAM)&toolInfo);
}

void ToolTip::SetDelayTime(UINT time)
{
    SendMessage(m_Hwnd, TTM_SETDELAYTIME, TTDT_INITIAL, (LPARAM)time);
}

void ToolTip::Activate(bool activate)
{
    SendMessage(m_Hwnd, TTM_ACTIVATE, (WPARAM)activate, 0);
}

void ToolTip::MakeToolTip(int flags, int maxwidth)
{
    if (m_parent)
        m_parent->AddToolTip(this);

	if (!m_parent)
		return;

	m_Hwnd = CreateWindowEx(
        WS_EX_TOPMOST,
        TOOLTIPS_CLASS,
        nullptr,
        WS_POPUP | TTS_NOPREFIX | TTS_BALLOON,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_parent->GetHandle(),
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );
    
    SET_ELEMENT_USERDATA(m_Hwnd, this);

    SendMessage(m_Hwnd, TTM_SETMAXTIPWIDTH, 0, 300);
}

void ToolTip::SetMaxTipWidth(int width) 
{
    SendMessage(m_Hwnd, TTM_SETMAXTIPWIDTH, 0, (LPARAM)width);
}

void ToolTip::SetTitle(const char* title) 
{
    SendMessage(m_Hwnd, TTM_SETTITLE, TTI_INFO, (LPARAM)title);
}

std::vector<Element*> ToolTip::GetUsedElements()
{
    return m_Elements;
}

ToolTip::~ToolTip()
{
    if (m_Hwnd)
        DestroyWindow(m_Hwnd);

    if (m_parent)
        m_parent->RemoveToolTip(this);
}
