#ifndef __TREEVIEW_H
#define __TREEVIEW_H

#include "Element.h"
#include "ImageList.h"
#include <CommCtrl.h>

#pragma once

#ifndef DEF_FLAGS_TREEVIEW
#define DEF_FLAGS_TREEVIEW WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS
#endif

namespace gui
{
	class TreeView : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(TreeView, Element);

		//doesnt create the tree view
		TreeView();

		//does create the tree view
		TreeView(Element* parent, const char* parentnodename, const int& command, HTREEITEM* root = nullptr);
		TreeView(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, const char* parentnodename /*if set to nullptr then wont create node*/, const char* classname, bool UseSubproc, ImageList* ImageList = nullptr,
			int parentnodeimage = 0, int parentnodeimageselected = 0, HTREEITEM* root = nullptr);

		virtual HTREEITEM AddNode(const char* text, HTREEITEM InsertParent = TVI_ROOT, HTREEITEM InsertAfter = TVI_LAST, int Mask = TVIF_TEXT, int image = 0, int selectedimage = 0);

		virtual void RemoveNode(HTREEITEM hItem);
		virtual void ExpandNode(HTREEITEM hItem);
		virtual void CollapseNode(HTREEITEM hItem);

		virtual HTREEITEM GetParentNode(HTREEITEM item);
		virtual HTREEITEM GetRootNode();

		virtual ImageList* GetImageList();
		virtual void SetImageList(ImageList* il);

		virtual unsigned int GetExtendedTreeViewStyle();
		virtual void SetExtendedTreeViewStyle(const unsigned int& style);

		virtual void SetTreeviewBgColor(COLORREF color);

		virtual void OnDeconstructor();

		virtual bool GetTreeItemName(HTREEITEM item, char* buf, int len);
		virtual void RenameTreeItem(HTREEITEM item, const char* newtext);

		virtual HTREEITEM GetTreeItemNextSibling(HTREEITEM item);
		virtual HTREEITEM GetTreeItemPreviousSibling(HTREEITEM item);
		virtual HTREEITEM GetTreeItemParent(HTREEITEM item);
		virtual HTREEITEM GetTreeItemChild(HTREEITEM item);
		virtual HTREEITEM GetTreeItemNextVisible(HTREEITEM item);
		virtual HTREEITEM GetTreeItemNextSelected(HTREEITEM item);
		virtual HTREEITEM GetTreeItemPreviousVisible(HTREEITEM item);

		virtual bool GetTreeItemCheckedState(HTREEITEM item);
		virtual void SetTreeItemCheckedState(HTREEITEM item, bool checked);

		virtual void StartTreeItemEditLabel(HTREEITEM item);
		virtual void StopTreeItemEditLabel(HTREEITEM item);

		virtual void DeleteTreeItem(HTREEITEM item);
		virtual void DeleteAllItems();

		virtual void ExpandTreeItem(HTREEITEM item, int code = TVE_EXPAND);

		virtual void SelectTreeItem(HTREEITEM item);

		virtual void EnsureTreeItemVisible(HTREEITEM item);

		virtual void SelectTreeItemDropTarget(HTREEITEM item);

		virtual int GetTreeItemIconIndex(HTREEITEM item, bool bSelected = false);
		virtual void SetTreeItemIconIndex(HTREEITEM item, int imageIndex, int selectedImageIndex = -1);

		virtual int GetSelectedCount();

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeTreeView(Element* parent, const char* parentnodename, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_TREEVIEW, int command = 0, bool UseSubproc = false, ImageList* ImageList = nullptr, int nParentNodeImage = 0, int nParentNodeSelectedImage = 0,
			HTREEITEM* root = nullptr);

		ImageList* m_ImageList;
		HTREEITEM m_Root;
	};

}

#endif
