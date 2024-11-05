#ifndef __LABEL_H
#define __LABEL_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_LABEL
#define DEF_FLAGS_LABEL WS_CHILD | WS_VISIBLE
#endif

namespace gui
{
	class Label : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(Label, Element)

		//doesnt make the Label
		Label();

		//does make the Label
		Label(Element* parent, const char* text, const int& command);
		Label(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* text, const char* classname);

		virtual void SetFont(HFONT font, BOOL bRedraw = TRUE);
		virtual HFONT GetFont();

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeLabel(Element* parent, const char* text, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_LABEL, int command = 0, bool UseSubproc = false);
	};
}

#endif