#ifndef __SCROLLWHEEL_H
#define __SCROLLWHEEL_H

#include "Element.h"
#include <CommCtrl.h>

#pragma once

#ifndef DEF_FLAGS_SCROLLWHEEL
#define DEF_FLAGS_SCROLLWHEEL WS_CHILD | WS_VISIBLE | WS_VSCROLL
#endif

namespace gui
{
    class ScrollWheel : public Element
    {
        DECLARE_ELEMENT_NOBASEPROC(ScrollWheel, Element);

        //doesnt make the ScrollWheel
        ScrollWheel();

        //does make the ScrollWheel
        ScrollWheel(Element* parent, const int& command);
        ScrollWheel(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, int minval, int maxval, int currval, const int& command, bool bUseSubproc, const char* classname);

        virtual void SetRange(int min, int max);
        virtual void SetValue(int pos);

        virtual int GetValue();

        DECLARE_ELEMENT_SUBPROC();
    protected:
        virtual bool MakeScrollWheel(Element* parent, int x, int y, int w, int h, long flags = DEF_FLAGS_SCROLLWHEEL, int minval = 0, int maxval = 10, int currval = 0, int command = 0, bool bUseSubproc = false);
    };
}

#endif
