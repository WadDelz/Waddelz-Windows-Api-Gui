#ifndef __CONTAINER_H
#define __CONTAINER_H

#include "Element.h"

#pragma once

#ifndef DEF_FLAGS_CONTAINER
#define DEF_FLAGS_CONTAINER WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN
#endif

namespace gui {
    class Container : public Element 
    {
        DECLARE_ELEMENT_NOBASEPROC(Container, Element);

        //doesnt make the Container
        Container();

        //does make the panel
        Container(Element* parent, int command);
        Container(Element* parent, int x, int y, int w, int h, int command, int flags, bool bUseSubproc, const char* classname = "Container");

        DECLARE_ELEMENT_SUBPROC();
    protected:
        virtual bool MakeContainer(Element* parent, int x, int y, int width, int height, int command, int flags, bool bUseSubproc);

        virtual int OnCommand(ELEMENT_PROC_ITEMS);
    };
}

#endif
