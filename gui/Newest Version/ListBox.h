#ifndef __LISTBOX_H
#define __LISTBOX_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_LISTBOX
#define DEF_FLAGS_LISTBOX WS_CHILD | WS_VISIBLE | LBS_NOTIFY
#endif

namespace gui
{
	class ListBox : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(ListBox, Element)

		// Doesn't make the ListBox
		ListBox();

		// Does Make The List Box
		ListBox(Element* parent, const int& command);
		ListBox(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const bool& bUseSubproc, const int& command, const char* classname);

		virtual void AddItem(const char* item);
		virtual void RemoveItem(int index);

		virtual void ClearItems();

		virtual void SetSelectedIndex(int index);
		virtual int GetSelectedIndex();

		virtual int GetNumItems();

		virtual void GetItemArray(char** arr);
		virtual int GetIndexFromString(const char* item);

		virtual int GetItemTextLength(int index);

		DECLARE_ELEMENT_SUBPROC();

	protected:
		virtual bool MakeListBox(Element* parent, int x, int y, int w, int h, long flags = DEF_FLAGS_LISTBOX, int command = 0, bool UseSubproc = false);
	};
}

#endif
