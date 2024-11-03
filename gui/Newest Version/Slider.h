#ifndef __SLIDER_H
#define __SLIDER_H

#include "Element.h"
#include <CommCtrl.h>

#pragma once

#ifndef DEF_FLAGS_SLIDER
#define DEF_FLAGS_SLIDER WS_CHILD | WS_VISIBLE | TBS_HORZ
#endif

namespace gui
{
	class Slider : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(Slider, Element)

		//doesnt make the Slider
		Slider();

		//does make the Slider
		Slider(Element* parent, const int& command);
		Slider(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const int& minval, const int& maxval, const int& val, const char* classname);

		virtual void OnDeconstructor();

		virtual int GetValue();
		virtual void SetValue(int value);

		virtual void GetRange(int& minval, int& maxval);
		virtual void SetRange(const int& minval, const int& maxval);

		DECLARE_ELEMENT_SUBPROC();
	protected:
		virtual bool MakeSlider(Element* parent, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_SLIDER, int command = 0, bool UseSubproc = false, const int& minval = 0, const int& maxval = 0, const int& val = 0);

		int m_iMinValue;
		int m_iMaxValue;
	};
}

#endif