#include "DatePicker.h"

using namespace gui;

START_ELEMENT_SUBPROC(DatePicker)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

DatePicker::DatePicker() : BaseClass()
{
    SetClassname("DatePicker");
}

DatePicker::DatePicker(Element* parent, const int& command) : BaseClass()
{
    SetClassname("DatePicker");
    MakeDatePicker(parent, 0, 0, 0, 0, DEF_FLAGS_DATEPICKER, command);
    parent->AddChild(this);
}

DatePicker::DatePicker(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* classname) : BaseClass()
{
    SetClassname(classname);
    MakeDatePicker(parent, x, y, w, h, flags, command);
    parent->AddChild(this);
}

static bool bDidInitCommonCtrls = false;

bool DatePicker::MakeDatePicker(Element* parent, int x, int y, int w, int h, long flags, int command, bool bUseSubproc)
{
    if (!parent)
        return false;

    if (!bDidInitCommonCtrls)
    {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_DATE_CLASSES;
        InitCommonControlsEx(&icex);
        bDidInitCommonCtrls = true;
    }

    m_Hwnd = CreateWindow(
        DATETIMEPICK_CLASS,
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
    if (bUseSubproc)
    {
        SetSubproc(ElementSubprocBase);
        ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
    }

    return true;
}

void DatePicker::SetDate(SYSTEMTIME* date)
{
    SendMessage(m_Hwnd, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)date);
}

void DatePicker::GetDate(SYSTEMTIME* date)
{
    SendMessage(m_Hwnd, DTM_GETSYSTEMTIME, 0, (LPARAM)date);
}

void DatePicker::SetRange(SYSTEMTIME* minDate, SYSTEMTIME* maxDate)
{
    SendMessage(m_Hwnd, DTM_SETRANGE, 0, (LPARAM)minDate);
    SendMessage(m_Hwnd, DTM_SETRANGE, 1, (LPARAM)maxDate);
}