#include "StatusBar.h"

using namespace gui;

START_ELEMENT_SUBPROC(StatusBar)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

StatusBar::StatusBar() : BaseClass()
{
    m_numParts = 0;
    SetClassname("StatusBar");
}

StatusBar::StatusBar(Element* parent, const char* text, int numParts, bool bUseSubproc, const char* classname) : BaseClass()
{
    m_numParts = numParts;
    SetClassname(classname);
    MakeStatusBar(parent, text, numParts, bUseSubproc);
    parent->AddChild(this);
}

static bool bDidInitCommonCtrls = false;

bool StatusBar::MakeStatusBar(Element* parent, const char* text, int numParts, bool bUseSubproc) 
{
    if (!parent)
        return false;

    if (!bDidInitCommonCtrls) 
    {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_BAR_CLASSES;
        InitCommonControlsEx(&icex);
        bDidInitCommonCtrls = true;
    }

    m_Hwnd = CreateWindow(
        STATUSCLASSNAME,
        nullptr,
        WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        parent->GetHandle(),
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    SET_ELEMENT_USERDATE(m_Hwnd, this);
    if (bUseSubproc)
    {
        SetSubproc(ElementSubprocBase);
        ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
    }

    SetParts(numParts);
    SetText(text);

    return true;
}
void StatusBar::SetParts(int numParts, int* partWidths) 
{
    m_numParts = numParts;
    if (!partWidths) 
    {
        int* autoWidths = new int[numParts];
        for (int i = 0; i < numParts; ++i)
        {
            autoWidths[i] = (i + 1) * 100;
        }
        SendMessage(m_Hwnd, SB_SETPARTS, numParts, (LPARAM)autoWidths);
        delete[] autoWidths;
    }
    else {
        SendMessage(m_Hwnd, SB_SETPARTS, numParts, (LPARAM)partWidths);
    }
}

void StatusBar::SetText(const char* text, int part, int style) 
{
    SendMessage(m_Hwnd, SB_SETTEXT, part | style, (LPARAM)text);
}

void StatusBar::OnSize(int width, int height) 
{
    SendMessage(m_Hwnd, WM_SIZE, 0, MAKELPARAM(width, height));
}

void StatusBar::OnSize(int lparam) 
{
    SendMessage(m_Hwnd, WM_SIZE, 0, lparam);
}

void StatusBar::OnDeconstructor()
{
    DeleteThis();
}
