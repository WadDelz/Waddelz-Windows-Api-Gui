#ifndef __STATUSBAR_H
#define __STATUSBAR_H

#include "Element.h"
#include <CommCtrl.h>

#pragma once

namespace gui 
{
    class StatusBar : public Element 
    {
        DECLARE_ELEMENT_NOBASEPROC(StatusBar, Element);

        // Doesnt Make The Status Bar
        StatusBar();

        //Does Make The Status Bar
        StatusBar(Element* parent, const char* text, int numParts = 0, bool bUseSubproc = false, const char* classname = "StatusBar");

        virtual void SetParts(int numParts, int* partWidths = nullptr);
        virtual void SetText(const char* text, int part = 0, int style = 0);

        virtual void OnSize(int width, int height);
        virtual void OnSize(int lparam);

        DECLARE_ELEMENT_SUBPROC();
    protected:
        virtual bool MakeStatusBar(Element* parent, const char* text, int numParts, bool bUseSubproc);

        int m_numParts;
    };
}

#endif
