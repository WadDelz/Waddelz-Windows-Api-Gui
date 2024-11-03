#ifndef __RICHEDIT_H
#define __RICHEDIT_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_RICHEDIT
#define DEF_FLAGS_RICHEDIT WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL
#endif

namespace gui
{
	class RichEdit : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(RichEdit, Element);

		//doesnt make the RichEdit
		RichEdit();

		//does make the RichEdit
		RichEdit(Element* parent, const char* text, const int& command);
		RichEdit(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* text, const char* classname);

		virtual void AppendText(const char* text);

		virtual void SetSelected(int start = -1, int end = -1);

		//use after SetSelected function
		virtual void SetSelectedTextColor(COLORREF color);

		//use after SetSelected function
		virtual void ReplaceSelectedText(const char* text, BOOL CaretMoveToEnd = TRUE);

		virtual void SetFont(HFONT hFont);
		virtual void SetTextColor(COLORREF color);
		virtual void SetTextSize(int size);
		virtual void SetTextBackgroundColor(COLORREF color);
		virtual void SetBackgroundColor(COLORREF color);
		virtual void ClearText();

		virtual HFONT GetDefaultFont();

		virtual int GetTextLength();

		virtual void OnDeconstructor();

		static void Init();
		static void Shutdown();

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeRichEdit(Element* parent, const char* text, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_RICHEDIT, int command = 0, bool UseSubproc = false);

		static HFONT m_DefaultFont;
		virtual HFONT GetDefaultFontBase();
	private:
		static HINSTANCE g_RichEditLibrary;
	};
}

#endif