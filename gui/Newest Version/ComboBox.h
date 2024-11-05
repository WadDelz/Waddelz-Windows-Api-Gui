#ifndef __COMBOBOX_H
#define __COMBOBOX_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_COMBOBOX
#define DEF_FLAGS_COMBOBOX WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL
#endif

namespace gui
{
	class ComboBox : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(ComboBox, Element)

		//doesnt make the ComboBox
		ComboBox();

		//does make the ComboBox
		ComboBox(Element* parent, const int& command);
		ComboBox(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& dropdownheight, const int& flags, const int& command, bool bUseSubproc, const char* classname);

		virtual void SelectItem(int index);
		virtual void SelectItem(const char* text);

		virtual void AddItem(const char* text);

		virtual int GetCurrentSelected();
		virtual int GetCount();

		virtual void DeleteAllItems();
		virtual void DeleteItem(int index);
		virtual void DeleteItem(const char* str);

		//IF YOU EVER SET THE DROPDOWN HEIGHT WITHOUT USING THE SetElementHeight FUNCTION
		//AND INSTEAD BY USING SendMessage(m_Hwnd, CB_SETITEMHEIGHT, -1, (LPARAM)height);
		//THEN SET THE m_ElementHeight INTIGER
		virtual void SetElementHeight(const int& height);
		virtual int GetElementHeight();

		//i remade these so i can add this comment
		//this doesnt set the actuall tall of the combo box but instead
		//the dropdown list itself. if you want to set the size
		//of the actuall combo box then use the SetElementHeight function
		virtual void SetTall(const int& tall) { BaseClass::SetTall(tall); }

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeComboBox(Element* parent, int x = 0, int y = 0, int w = 0, int h = 0, int dropdownheight = 0, long flags = DEF_FLAGS_COMBOBOX, int command = 0, bool UseSubproc = false);

		int m_ElementHeight;
	};
}

#endif