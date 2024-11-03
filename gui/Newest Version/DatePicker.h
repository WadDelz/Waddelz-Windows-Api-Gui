#ifndef __DATEPICKER_H
#define __DATEPICKER_H

#include "Element.h"
#include <windows.h>
#include <commctrl.h>

#pragma once

#ifndef DEF_FLAGS_DATEPICKER
#define DEF_FLAGS_DATEPICKER WS_CHILD | WS_VISIBLE | WS_BORDER
#endif

namespace gui
{
    class DatePicker : public Element
    {
        DECLARE_ELEMENT_NOBASEPROC(DatePicker, Element);

        //doesnt make the DatePicker
        DatePicker();

        //does make the DatePicker
        DatePicker(Element* parent, const int& command);
        DatePicker(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* classname);

        virtual void SetDate(SYSTEMTIME* date);
        virtual void GetDate(SYSTEMTIME* date);

        void SetRange(SYSTEMTIME* minDate, SYSTEMTIME* maxDate);

        DECLARE_ELEMENT_SUBPROC();
    protected:
        virtual bool MakeDatePicker(Element* parent, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_DATEPICKER, int command = 0, bool bUseSubproc = false);
    };
}

#endif
