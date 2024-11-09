#ifndef __CUSTOMITEM_H
#define __CUSTOMITEM_H

#include "Element.h"

#pragma once

namespace gui
{
	class CustomItem : public Element
	{
	public:
		DECLARE_ELEMENT_NOBASEPROC(CustomItem, Element);

		//doesnt make the CustomItem
		CustomItem();

		//does make the CustomItem
		CustomItem(Element* parent, const char* wndclassname, int command);
		CustomItem(Element* parent, const char* wndclassname, const char* text, int flags, int x, int y, int w, int h, int command, bool bUseSubproc = false, const char* classname = "CustomItem");

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeItem(Element* parent, const char* wndclassname, const char* text, int flags, int x, int y, int w, int h, int command, bool bUseSubproc = false);
	};

	bool RegisterCustomItem(
		LPCSTR classname,
		WNDPROC wndproc,
		HINSTANCE instance = GetModuleHandle(nullptr),
		HICON icon = nullptr,
		HBRUSH hbrbackground = nullptr,
		HCURSOR cursor = nullptr,
		INT style = 0,
		LPCSTR lpszMenuName = nullptr
	);
}

#endif