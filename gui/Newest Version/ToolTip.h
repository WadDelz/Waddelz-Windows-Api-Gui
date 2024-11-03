#ifndef __TOOLTIP_H
#define __TOOLTIP_H

#include "Element.h"
#include <CommCtrl.h>

#pragma once

#ifndef DEF_FLAGS_TOOLTIP
#define DEF_FLAGS_TOOLTIP WS_POPUP | TTS_NOPREFIX | TTS_BALLOON
#endif

namespace gui
{
	class ToolTip
	{
	public:
		//doesnt make the ToolTip
		ToolTip();

		//does make the ToolTip
		ToolTip(Element* parent, int flags = DEF_FLAGS_TOOLTIP, int maxwidth = 300);

		virtual void AddTool(Element* toolelement, const char* text);
		virtual void AddTool(HWND toolhwnd, const char* text);

		void RemoveTool(HWND hwnd);
		void RemoveTool(Element* element);

		virtual void UpdateToolText(Element* toolelement, const char* text);
		virtual void UpdateToolText(HWND toolhwnd, const char* text);

		virtual void SetDelayTime(UINT time);
		virtual void Activate(bool activate);

		void SetMaxTipWidth(int width);
		void SetTitle(const char* title);

		std::vector<Element*> GetUsedElements();

		~ToolTip();
	protected:
		virtual void MakeToolTip(int flags, int maxwidth);
	protected:
		Element* m_parent;
		std::vector<Element*> m_Elements;

		HWND m_Hwnd;
	};
}

#endif