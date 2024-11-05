#include "TreeView.h"

#pragma comment (lib, "comctl32.lib")

using namespace gui;

START_ELEMENT_SUBPROC(TreeView)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

TreeView::TreeView() : BaseClass()
{
	m_ImageList = nullptr;
	m_Root = nullptr;

	SetClassname("TreeView");
}

TreeView::TreeView(Element* parent, const char* parentnodename, const int& command, HTREEITEM* root) : BaseClass()
{
	m_ImageList = nullptr;
	m_Root = nullptr;

	SetClassname("TreeView");
	MakeTreeView(parent, parentnodename, 0, 0, 0, 0, DEF_FLAGS_TREEVIEW, command, false, nullptr, 0, 0, root);
	parent->AddChild(this);
}

TreeView::TreeView(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, const char* parentnodename, const char* classname, bool UseSubproc, ImageList* il, int parentnodeimage, int parentnodeimageselected, HTREEITEM* root) : BaseClass()
{
	m_ImageList = il;
	m_Root = nullptr;

	SetClassname(classname);
	MakeTreeView(parent, parentnodename, x, y, w, h, flags, command, UseSubproc, il, parentnodeimage, parentnodeimageselected);
	parent->AddChild(this);
}

static bool bDidInitCommonCtrls = false;

bool TreeView::MakeTreeView(Element* parent, const char* parentnodename, int x, int y, int w, int h, long flags, int command, bool UseSubproc, ImageList* imagelist, int nParentNodeImage, int nParentNodeSelectedImage, HTREEITEM* root)
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
		WC_TREEVIEW,
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

	if (imagelist)
		TreeView_SetImageList(m_Hwnd, imagelist->GetImageList(), TVSIL_NORMAL);

	m_ImageList = imagelist;

	if (parentnodename)
	{
		int flags = TVIF_TEXT;
		if (imagelist)
			flags = (flags | TVIF_IMAGE | TVIF_SELECTEDIMAGE);

		HTREEITEM item = AddNode(parentnodename, nullptr, TVI_ROOT, flags, nParentNodeImage, nParentNodeSelectedImage);
		if (root)
			*root = m_Root = item;
	}

	SET_ELEMENT_USERDATA(m_Hwnd, this);
	if (UseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}

	return true;
}

HTREEITEM TreeView::AddNode(const char* text, HTREEITEM InsertParent, HTREEITEM InsertAfter, int Mask, int image, int selectedimage)
{
	TVINSERTSTRUCT tvis;
	ZeroMemory(&tvis, sizeof(tvis));
	tvis.hParent = InsertParent;
	tvis.hInsertAfter = InsertAfter;
	tvis.item.mask = Mask;
	tvis.item.iImage = image;
	tvis.item.iSelectedImage = selectedimage;
	tvis.item.pszText = (LPSTR)text;

	return (HTREEITEM)SendMessage(m_Hwnd, TVM_INSERTITEM, 0, (LPARAM)&tvis);
}

void TreeView::RemoveNode(HTREEITEM hItem)
{
	if (hItem)
		SendMessage(m_Hwnd, TVM_DELETEITEM, 0, (LPARAM)hItem);
}

void TreeView::ExpandNode(HTREEITEM hItem)
{
	SendMessage(m_Hwnd, TVM_EXPAND, TVE_EXPAND, (LPARAM)hItem);
}

void TreeView::CollapseNode(HTREEITEM hItem)
{
	SendMessage(m_Hwnd, TVM_EXPAND, TVE_COLLAPSE, (LPARAM)hItem);
}

HTREEITEM TreeView::GetParentNode(HTREEITEM item)
{
	return TreeView_GetParent(m_Hwnd, item);
}

HTREEITEM TreeView::GetRootNode()
{
	return m_Root;
}

ImageList* TreeView::GetImageList()
{
	return m_ImageList;
}

void TreeView::SetImageList(ImageList* il)
{
	TreeView_SetImageList(m_Hwnd, il->GetImageList(), TVSIL_NORMAL);
	m_ImageList = il;
}

unsigned int TreeView::GetExtendedTreeViewStyle()
{
	return TreeView_GetExtendedStyle(m_Hwnd);
}

void TreeView::SetExtendedTreeViewStyle(const unsigned int& style)
{
	TreeView_SetExtendedStyle(m_Hwnd, style, style);
}

void TreeView::SetTreeviewBgColor(COLORREF color)
{
	TreeView_SetBkColor(m_Hwnd, color);
}

bool TreeView::GetTreeItemName(HTREEITEM item, char* buf, int len)
{
	TVITEM tvi;
	tvi.mask = TVIF_TEXT;
	tvi.hItem = item;
	tvi.pszText = buf;
	tvi.cchTextMax = len;

	if (TreeView_GetItem(m_Hwnd, &tvi))
		return true;

	return false;
}

void TreeView::RenameTreeItem(HTREEITEM item, const char* newtext)
{
	TVITEM tvi = { 0 };
	tvi.mask = TVIF_TEXT;
	tvi.hItem = item;
	tvi.pszText = (LPSTR)newtext;
	tvi.cchTextMax = strlen(newtext);

	TreeView_SetItem(m_Hwnd, &tvi);
}

HTREEITEM TreeView::GetTreeItemNextSibling(HTREEITEM item)
{
	return TreeView_GetNextSibling(m_Hwnd, item);
}

HTREEITEM TreeView::GetTreeItemPreviousSibling(HTREEITEM item)
{
	return TreeView_GetPrevSibling(m_Hwnd, item);
}

HTREEITEM TreeView::GetTreeItemParent(HTREEITEM item)
{
	return TreeView_GetParent(m_Hwnd, item);
}

HTREEITEM TreeView::GetTreeItemChild(HTREEITEM item)
{
	return TreeView_GetChild(m_Hwnd, item);
}

HTREEITEM TreeView::GetTreeItemNextVisible(HTREEITEM item)
{
	return TreeView_GetNextVisible(m_Hwnd, item);
}

HTREEITEM TreeView::GetTreeItemNextSelected(HTREEITEM item)
{
	return TreeView_GetNextSelected(m_Hwnd, item);
}

HTREEITEM TreeView::GetTreeItemPreviousVisible(HTREEITEM item)
{
	return TreeView_GetPrevVisible(m_Hwnd, item);
}

bool TreeView::GetTreeItemCheckedState(HTREEITEM item)
{
	TVITEM tvi = { 0 };
	tvi.mask = TVIF_HANDLE | TVIF_STATE;
	tvi.hItem = item;
	tvi.stateMask = TVIS_STATEIMAGEMASK;

	if (TreeView_GetItem(m_Hwnd, &tvi)) 
	{
		int stateIndex = (tvi.state >> 12) & 0xF;
		return (stateIndex == 2);
	}

	return false;
}

void TreeView::SetTreeItemCheckedState(HTREEITEM item, bool checked)
{
	TVITEM tvi = { 0 };
	tvi.mask = TVIF_HANDLE | TVIF_STATE;
	tvi.hItem = item;
	tvi.stateMask = TVIS_STATEIMAGEMASK;

	tvi.state = INDEXTOSTATEIMAGEMASK(checked ? 2 : 1);

	TreeView_SetItem(m_Hwnd, &tvi);
}

void TreeView::StartTreeItemEditLabel(HTREEITEM item)
{
	TreeView_EditLabel(m_Hwnd, item);
}

void TreeView::StopTreeItemEditLabel(HTREEITEM item)
{
	TreeView_EndEditLabelNow(m_Hwnd, item);
}

void TreeView::DeleteTreeItem(HTREEITEM item)
{
	if (item == m_Root)
		m_Root = nullptr;

	TreeView_DeleteItem(m_Hwnd, item);
}

void TreeView::DeleteAllItems()
{
	TreeView_DeleteAllItems(m_Hwnd);
}

void TreeView::ExpandTreeItem(HTREEITEM item, int code)
{
	TreeView_Expand(m_Hwnd, item, code);
}

void TreeView::SelectTreeItem(HTREEITEM item)
{
	TreeView_SelectItem(m_Hwnd, item);
}

void TreeView::EnsureTreeItemVisible(HTREEITEM item)
{
	TreeView_EnsureVisible(m_Hwnd, item);
}

void TreeView::SelectTreeItemDropTarget(HTREEITEM item)
{
	TreeView_SelectDropTarget(m_Hwnd, item);
}

int TreeView::GetSelectedCount()
{
	return TreeView_GetSelectedCount(m_Hwnd);
}

void TreeView::SetTreeItemIconIndex(HTREEITEM item, int imageIndex, int selectedImageIndex)
{
	TVITEM tvi = {};
	tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvi.hItem = item;
	tvi.iImage = imageIndex;

	tvi.iSelectedImage = (selectedImageIndex != -1) ? selectedImageIndex : imageIndex;

	SendMessage(m_Hwnd, TVM_SETITEM, 0, (LPARAM)&tvi);
}

int TreeView::GetTreeItemIconIndex(HTREEITEM item, bool bSelected)
{
	TVITEM tvi = {};
	tvi.hItem = item;
	tvi.mask = TVIF_IMAGE;

	if (bSelected)
		tvi.mask |= TVIF_SELECTEDIMAGE;

	if (SendMessage(m_Hwnd, TVM_GETITEM, 0, (LPARAM)&tvi))
	{
		if (bSelected)
			return tvi.iSelectedImage;
		else
			return tvi.iImage;
	}

	return -1;
}
