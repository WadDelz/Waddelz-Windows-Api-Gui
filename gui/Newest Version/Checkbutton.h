#ifndef __CHECKBUTTON_H
#define __CHECKBUTTON_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_CHECKBUTTON
#define DEF_FLAGS_CHECKBUTTON WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX
#endif

namespace gui
{
	class CheckButton : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(CheckButton, Element)

		//doesnt make the button
		CheckButton();

		//does make the button
		CheckButton(Element* parent, const char* text, const int& command);
		CheckButton(Element* parent, const char* text, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bChecked, bool bUseSubproc, const char* classname);

		virtual bool IsChecked();
		virtual void SetChecked(const bool& bChecked);

		virtual void OnDeconstructor();

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeCheckbutton(Element* parent, const char* text, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_CHECKBUTTON, int command = 0, bool bChecked = false, bool UseSubproc = false);
	};
}

#endif