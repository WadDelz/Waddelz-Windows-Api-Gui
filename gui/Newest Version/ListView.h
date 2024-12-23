#ifndef __LISTVIEW_H
#define __LISTVIEW_H

#include "Element.h"
#include "ImageList.h"
#include <CommCtrl.h>

#pragma once

#ifndef DEF_FLAGS_LISTVIEW
#define DEF_FLAGS_LISTVIEW WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_NOSORTHEADER
#endif

//NOTE:
//for now the imagelist doesnt work untill i fix it (:

namespace gui
{
    class ListView : public Element
    {
        DECLARE_ELEMENT_NOBASEPROC(ListView, Element);

        //doesnt make the ListView
        ListView();

        //does make the ListView
        ListView(Element* parent, const int& command);
        ListView(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, const char* classname, bool UseSubproc, ImageList* imageList = nullptr);

        virtual void AddColumn(const char* text, int width, int index = -1);
        virtual void AddItem(const char* text, int row, int subItem = 0, int imageIndex = 0);
        virtual void RemoveItem(int index);

        virtual int GetColumnCount();

        virtual unsigned int GetExtendedListViewStyle();
        virtual void SetExtendedListViewStyle(const unsigned int& style);

        //the verticle row
        virtual int GetSelectedRow();
        virtual bool GetItemText(char* buf, int size, int row /*verticle row*/, int horizrow /*horizontal row*/ = 0, unsigned int flags = LVIF_TEXT);

        virtual void SetImageList(ImageList* il);
        virtual ImageList* GetImageList();

        DECLARE_ELEMENT_SUBPROC();
    protected:
        virtual bool MakeListView(Element* parent, int x = 0, int y = 0, int w = 0, int h = 0, long flags = DEF_FLAGS_LISTVIEW, int command = 0, bool UseSubproc = false, ImageList* imageList = nullptr);

        ImageList* m_ImageList;
    };
}

#endif
