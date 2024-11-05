#include "ListView.h"

using namespace gui;

START_ELEMENT_SUBPROC(ListView)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

ListView::ListView() : BaseClass()
{
    m_ImageList = nullptr;
    SetClassname("ListView");
}

ListView::ListView(Element* parent, const int& command) : BaseClass()
{
    m_ImageList = nullptr;
    SetClassname("ListView");
    MakeListView(parent, 0, 0, 0, 0, DEF_FLAGS_LISTVIEW, command);
    parent->AddChild(this);
}

ListView::ListView(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, const char* classname, bool UseSubproc, ImageList* imageList) : BaseClass()
{
    m_ImageList = imageList;
    SetClassname(classname);
    MakeListView(parent, x, y, w, h, flags, command, UseSubproc, imageList);
    parent->AddChild(this);
}

static bool bDidInitCommonCtrls = false;

bool ListView::MakeListView(Element* parent, int x, int y, int w, int h, long flags, int command, bool UseSubproc, ImageList* imageList)
{
    if (!parent)
        return false;

    if (!bDidInitCommonCtrls)
    {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_TREEVIEW_CLASSES;
        InitCommonControlsEx(&icex);
        bDidInitCommonCtrls = true;
    }

    m_Hwnd = CreateWindow(
        WC_LISTVIEW,
        "",
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

    if (imageList)
        SetImageList(imageList);

    SET_ELEMENT_USERDATA(m_Hwnd, this);
    if (UseSubproc)
    {
        SetSubproc(ElementSubprocBase);
        ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
    }

    return true;
}

void ListView::AddColumn(const char* text, int width, int index)
{
    LVCOLUMN lvc;
    ZeroMemory(&lvc, sizeof(LVCOLUMN));
    lvc.mask = LVCF_TEXT | LVCF_WIDTH;
    lvc.pszText = (LPSTR)text;
    lvc.cx = width;

    if (index >= 0)
        ListView_InsertColumn(m_Hwnd, index, &lvc);
    else
        ListView_InsertColumn(m_Hwnd, GetColumnCount(), &lvc);
}

void ListView::AddItem(const char* text, int index, int subItem, int imageIndex)
{
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));
    lvi.mask = LVIF_TEXT;
    lvi.pszText = (LPSTR)text;
    lvi.iImage = imageIndex;

    if (imageIndex >= 0) {
        lvi.mask |= LVIF_IMAGE;
        lvi.iImage = imageIndex;
    }


    if (subItem == 0) 
    {
        lvi.iItem = index >= 0 ? index : ListView_GetItemCount(m_Hwnd);
        lvi.iSubItem = 0;
        lvi.mask |= LVIF_IMAGE;
        ListView_InsertItem(m_Hwnd, &lvi);
    }
    else 
    {
        lvi.iItem = index;
        lvi.iSubItem = subItem;
        ListView_SetItem(m_Hwnd, &lvi);
    }
}


void ListView::RemoveItem(int index)
{
    if (index >= 0)
        ListView_DeleteItem(m_Hwnd, index);
}

int ListView::GetColumnCount()
{
    LVCOLUMN col;
    col.mask = LVCF_TEXT;
    int count = 0;
    while (ListView_GetColumn(m_Hwnd, count, &col)) {
        count++;
    }
    return count;
}

unsigned int ListView::GetExtendedListViewStyle()
{
    return ListView_GetExtendedListViewStyle(m_Hwnd);
}

void ListView::SetExtendedListViewStyle(const unsigned int& style)
{
    ListView_SetExtendedListViewStyle(m_Hwnd, style);
}

int ListView::GetSelectedRow()
{
    return ListView_GetNextItem(m_Hwnd, -1, LVNI_SELECTED);
}

bool ListView::GetItemText(char* buf, int size, int row, int horizrow, unsigned int flags)
{
    if (!buf)
        return false;

    LVITEM lvItem;
    lvItem.iItem = row;
    lvItem.iSubItem = horizrow;
    lvItem.mask = flags;
    lvItem.cchTextMax = size;
    lvItem.pszText = buf;
    
    if (ListView_GetItem(m_Hwnd, &lvItem))
        return true;

    return false;
}

void ListView::SetImageList(ImageList* il)
{
    ListView_SetImageList(m_Hwnd, il->GetImageList(), LVSIL_NORMAL);
    m_ImageList = il;
}

ImageList* ListView::GetImageList()
{
    return m_ImageList;
}