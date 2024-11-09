#include "Container.h"
#include "Window.h"

using namespace gui;

//change this if you want to
#define CONTAINER_GO_TO_PARENT 1

START_ELEMENT_SUBPROC(Container)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);

#if CONTAINER_GO_TO_PARENT
END_PROC(OnCommand(ELEMENT_ITEMS))
#else
END_ELEMENT_PROC(CallWindowProc(m_DefaultProc, hwnd, msg, wp, lp))
#endif

Container::Container() : BaseClass()
{
	SetClassname("Container");
}

Container::Container(Element* parent, int command) : BaseClass()
{
	SetClassname("Container");
	MakeContainer(parent, 0, 0, 0, 0,  command, DEF_FLAGS_CONTAINER, true);
	parent->AddChild(this);
}

Container::Container(Element* parent, int x, int y, int w, int h, int command, int flags, bool bUseSubproc, const char* classname) : BaseClass()
{
	SetClassname(classname);
	MakeContainer(parent, x, y, w, h, command, flags, bUseSubproc);
	parent->AddChild(this);
}

bool Container::MakeContainer(Element* parent, int x, int y, int width, int height, int command, int flags, bool bUseSubproc)
{
	m_iCommandId = command;

	if (!parent)
		return false;

	m_Hwnd = CreateWindow(
		"STATIC",
		"",
		flags,
		50, 50,
		200, 150,
		parent->GetHandle(),
		(HMENU)command,
		GetModuleHandle(nullptr),
		NULL);


	SetVisible(true);
	SetEnabled(true);

	SET_ELEMENT_USERDATA(m_Hwnd, this);
	if (bUseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}

	return true;
}

//TODO: fix this for sub dialogs
int Container::OnCommand(ELEMENT_PROC_ITEMS)
{
	Window* parent = (Window*)m_Parent;
	if (parent)
		parent->ElementProc(ELEMENT_ITEMS);

	return CALL_DEF_SUBPROC();
}
