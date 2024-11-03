#ifndef __LOADINGBAR_H
#define __LOADINGBAR_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_LOADINGBAR
#define DEF_FLAGS_LOADINGBAR WS_CHILD | WS_VISIBLE
#endif

namespace gui
{
	class LoadingBar : public Element
	{
		DECLARE_ELEMENT_NOBASEPROC(LoadingBar, Element);

		//doesnt make the LoadingBar
		LoadingBar();

		//does make the loading bar
		LoadingBar(Element* parent, int min = 0, int max = 100, int initialPos = 0);
		LoadingBar(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, int min, int max, int initialPos, bool UseSubproc = false, const char* classname = "LoadingBar");

		virtual void SetRange(int min, int max);
		virtual void SetPosition(int pos);
		virtual int GetPosition();
		virtual void StepIt(int step = 1);

		virtual void OnDeconstructor();

		DECLARE_ELEMENT_SUBPROC();

	protected:
		virtual bool MakeLoadingBar(Element* parent, int x = 0, int y = 0, int w = 100, int h = 20, long flags = DEF_FLAGS_LOADINGBAR, int min = 0, int max = 100, int initialPos = 0, bool UseSubproc = false);
	};
}

#endif
