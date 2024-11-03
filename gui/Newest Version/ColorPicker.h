#ifndef __COLORPICKER_H
#define __COLORPICKER_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_COLORPICKER
#define DEF_FLAGS_COLORPICKER CC_FULLOPEN | CC_RGBINIT
#endif

namespace gui
{
	class ColorPicker
	{
	public:
		ColorPicker();
		ColorPicker(Element* element);

		virtual bool ShowDialog(const int& flags = DEF_FLAGS_COLORPICKER, COLORREF customcolors[16] = nullptr);

		virtual COLORREF GetColor();

		virtual void SetElement(Element* element);
		virtual Element* GetElement();
	protected:
		Element* m_Parent;
		COLORREF m_Color;

		static COLORREF DefColorPreset[16];
	};
}

#endif