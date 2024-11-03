#include "ScrollWheel.h"

using namespace gui;

START_ELEMENT_SUBPROC(ScrollWheel)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

ScrollWheel::ScrollWheel() : BaseClass() 
{
    SetClassname("ScrollWheel");
}

ScrollWheel::ScrollWheel(Element* parent, const int& command) : BaseClass()
{
    SetClassname("ScrollWheel");
    MakeScrollWheel(parent, 0, 0, 0, 0, DEF_FLAGS_SCROLLWHEEL, 0, 10, 0, command);
    parent->AddChild(this);
}

ScrollWheel::ScrollWheel(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, int minval, int maxval, int currval, const int& command, bool bUseSubproc, const char* classname) : BaseClass()
{
    SetClassname(classname);
    MakeScrollWheel(parent, x, y, w, h, flags, minval, maxval, currval, command, bUseSubproc);
    parent->AddChild(this);
}

bool ScrollWheel::MakeScrollWheel(Element* parent, int x, int y, int w, int h, long flags, int minval, int maxval, int currval, int command, bool bUseSubproc)
{
    if (!parent)
        return false;

    m_Hwnd = CreateWindow(
        WC_SCROLLBAR,
        "",
        flags,
        x, y,
        w, h,
        parent->GetHandle(),
        (HMENU)command,
        GetModuleHandle(nullptr),
        nullptr
    );

    SetRange(minval, maxval);
    SetValue(currval);

    SET_ELEMENT_USERDATE(m_Hwnd, this);
    if (bUseSubproc)
    {
        SetSubproc(ElementSubprocBase);
        ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
    }

    SetVisible(true);
    SetEnabled(true);

    return true;
}

void ScrollWheel::SetRange(int min, int max)
{
    SetScrollRange(m_Hwnd, SB_VERT, min, max, TRUE);
}

void ScrollWheel::SetValue(int pos)
{
    SetScrollPos(m_Hwnd, SB_VERT, pos, TRUE);
}

int ScrollWheel::GetValue()
{
    return GetScrollPos(m_Hwnd, SB_VERT);
}