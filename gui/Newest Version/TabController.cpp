#include "TabController.h"

using namespace gui;

START_ELEMENT_SUBPROC(TabController)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

TabController::TabController() : BaseClass()
{
    SetClassname("TabController");
}

TabController::TabController(Element* parent, int command) : BaseClass()
{
    SetClassname("TabController");
    MakeTabControl(parent, 0, 0, 0, 0, DEF_FLAGS_TABCONTROLLER, command, false);
    parent->AddChild(this);
}

TabController::TabController(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* classname) : BaseClass()
{
    SetClassname(classname);
    MakeTabControl(parent, x, y, w, h, flags, command, bUseSubproc);
    parent->AddChild(this);
}

static bool bDidInitCommonCtrls = false;

bool TabController::MakeTabControl(Element* parent, int x, int y, int w, int h, long flags, int command, bool bUseSubproc)
{
    if (!parent)
        return false;

    if (!bDidInitCommonCtrls)
    {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_TAB_CLASSES;
        InitCommonControlsEx(&icex);
        bDidInitCommonCtrls = true;
    }

    m_Hwnd = CreateWindow(
        WC_TABCONTROL,
        "",
        flags,
        x, y,
        w, h,
        parent->GetHandle(),
        (HMENU)command,
        GetModuleHandle(nullptr),
        nullptr
    );

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

void TabController::AddTab(const char* text, int index)
{
    TCITEM tie;
    tie.mask = TCIF_TEXT;

    tie.pszText = (LPSTR)text;
    if (index >= 0)
        TabCtrl_InsertItem(m_Hwnd, index, &tie);
    else
        TabCtrl_InsertItem(m_Hwnd, TabCtrl_GetItemCount(m_Hwnd), &tie);
}

void TabController::RemoveTab(int index)
{
    if (index >= 0)
        TabCtrl_DeleteItem(m_Hwnd, index);
}

int TabController::GetTabCount()
{
    return TabCtrl_GetItemCount(m_Hwnd);
}

void TabController::SelectTab(int tab)
{
    TabCtrl_SetCurSel(m_Hwnd, tab);
    TabCtrl_SetCurFocus(m_Hwnd, tab);
}

int TabController::GetCurrentSelected()
{
    return TabCtrl_GetCurSel(m_Hwnd);
}

void TabController::SetTabSize(int wide, int tall)
{
    SendMessage(m_Hwnd, TCM_SETITEMSIZE, 0, MAKELPARAM(wide, tall));

    InvalidateRect(m_Hwnd, NULL, TRUE);
    UpdateWindow(m_Hwnd);
}

void TabController::GetTabSize(int& wide, int& tall)
{
    RECT rect;
    int tabIndex = 0;

    if (SendMessage(m_Hwnd, TCM_GETITEMRECT, tabIndex, (LPARAM)&rect)) {
        wide = rect.right - rect.left;
        tall = rect.bottom - rect.top;
    }

}

void TabController::OnDeconstructor()
{
    DeleteThis();
}
