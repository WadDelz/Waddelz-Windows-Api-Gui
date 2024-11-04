#ifndef __TOOLBAR_H
#define __TOOLBAR_H

#include "Element.h"
#include "ImageList.h"

#pragma once

#ifndef DEF_FLAGS_TOOLBAR
#define DEF_FLAGS_TOOLBAR WS_CHILD | WS_VISIBLE | TBSTYLE_WRAPABLE
#endif

namespace gui
{
	class ToolBar
	{
	public:
		//doesnt make the ToolBar
		ToolBar();

		//makes the ToolBar
		ToolBar(Element* parent, ImageList* il = nullptr, int flags = DEF_FLAGS_TOOLBAR);

		virtual void AddButton(int command, int state = TBSTATE_ENABLED, int style = TBSTYLE_BUTTON, int ibitmap = 0);

		virtual void SetImageList(ImageList* imagelist, bool bDeleteOld = true);
		virtual ImageList* GetImageList();

		virtual bool IsButtonEnabled(int command);
		virtual void EnableButton(int command, bool enable);

		virtual int GetButtonCount();

		virtual bool IsButtonPressedDown(int command);
		virtual void SetButtonPressedDown(int command, bool checked);

		virtual bool IsStateEnabled(int command, int state);

		virtual void SetButtonImageIndex(int command, int index);
		virtual int GetButtonIconIndex(int command);

		virtual void SetX(int x);
		virtual void SetY(int y);
		virtual void SetWidth(int width);
		virtual void SetTall(int height);
		virtual void SetPos(int x, int y);
		virtual void SetSize(int width, int height);
		virtual void SetBounds(int x, int y, int width, int height);

		virtual void GetX(int* x);
		virtual void GetY(int* y);
		virtual void GetWidth(int* width);
		virtual void GetTall(int* height);
		virtual void GetPos(int* x, int* y);
		virtual void GetSize(int* width, int* height);
		virtual void GetBounds(int* x, int* y, int* width, int* height);
	protected:
		virtual bool MakeToolBar(Element* parent, int flags = DEF_FLAGS_TOOLBAR, ImageList* il = nullptr);
	protected:
		HWND m_Hwnd;
		ImageList* m_ImageList;
		Element* m_Parent;
	};
}

#endif