#ifndef __TABCONTROLLER_H
#define __TABCONTROLLER_H

#include "Element.h"
#include <CommCtrl.h>

#pragma once

#ifndef DEF_FLAGS_TABCONTROLLER
#define DEF_FLAGS_TABCONTROLLER WS_CHILD | WS_VISIBLE | WS_BORDER | TCS_TABS
#endif

namespace gui
{
    class TabController : public Element
    {
        DECLARE_ELEMENT_NOBASEPROC(TabController, Element);

        //doesnt make the TabController
        TabController();

        //does make the TabController
        TabController(Element* parent, int command);
        TabController(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const char* classname);

        virtual void AddTab(const char* text, int index = -1);
        virtual void RemoveTab(int index);
        
        virtual int GetTabCount();

        virtual void SelectTab(int tab);
        virtual int GetCurrentSelected();

        //ONLY SETS THE TAB TALL NOT WIDE 
        //TODO: FIXME
        virtual void SetTabSize(int wide, int tall);

        virtual void GetTabSize(int& wide, int& tall);

        virtual void OnDeconstructor();

        virtual void SetExtendedTabCtrlStyle(unsigned int style);
        virtual unsigned int GetExtendedTabCtrlStyle();

        DECLARE_ELEMENT_SUBPROC()
    protected:
        virtual bool MakeTabControl(Element* parent, int x, int y, int w, int h, long flags = DEF_FLAGS_TABCONTROLLER, int command = 0, bool bUseSubproc = false);

    };
}

#endif
