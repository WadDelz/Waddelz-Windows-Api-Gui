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

	SET_ELEMENT_USERDATE(m_Hwnd, this);
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

void TreeView::SetTreeviewBgColor(COLORREF color)
{
	TreeView_SetBkColor(m_Hwnd, color);
}

void TreeView::OnDeconstructor()
{
	DeleteThis();
}
