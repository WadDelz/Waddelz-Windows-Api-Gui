#ifndef __BUTTON_H
#define __BUTTON_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_BUTTON
#define DEF_FLAGS_BUTTON WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
#endif

namespace gui
{
	class Button : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(Button, Element)

		//doesnt make the button
		Button();

		//does make the button
		Button(Element* parent, const char* text, const int& command);
		Button(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* text, const char* classname);

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeButton(Element* parent, const char* text, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_BUTTON, int command = 0, bool UseSubproc = false);
	};
}

#endif