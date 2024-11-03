#ifndef __TEXTENTRY_H
#define __TEXTENTRY_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_TEXTENTRY
#define DEF_FLAGS_TEXTENTRY WS_VISIBLE | WS_CHILD | WS_BORDER
#endif

namespace gui
{
	class TextEntry : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(TextEntry, Element)

		//doesnt make the TextEntry
		TextEntry();

		//does make the TextEntry
		TextEntry(Element* parent, const char* text, const int& command);
		TextEntry(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* text, const char* classname);

		virtual void SetSelected(int start = -1, int end = -1);

		//use after SetSelected function
		virtual void ReplaceSelectedText(const char* text, BOOL CaretMoveToEnd = TRUE);
		virtual void AppendText(const char* text);

		virtual int GetTextLength();
		virtual void ClearText();

		virtual void OnDeconstructor();

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeTextEntry(Element* parent, const char* text, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_TEXTENTRY, int command = 0, bool UseSubproc = false);
	};
}

#endif