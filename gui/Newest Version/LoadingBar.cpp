#include "LoadingBar.h"
#include <CommCtrl.h> // For Progress Bar control

using namespace gui;

START_ELEMENT_SUBPROC(LoadingBar)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_ELEMENT_PROC(CALL_DEF_SUBPROC())

LoadingBar::LoadingBar() : BaseClass()
{
	SetClassname("LoadingBar");
}

LoadingBar::LoadingBar(Element* parent, int min, int max, int initialPos) : BaseClass()
{
	SetClassname("LoadingBar");
	MakeLoadingBar(parent, 0, 0, 100, 20, DEF_FLAGS_LOADINGBAR, min, max, initialPos);
	parent->AddChild(this);
}

LoadingBar::LoadingBar(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, int min, int max, int initialPos, bool UseSubproc, const char* classname) : BaseClass()
{
	SetClassname(classname);
	MakeLoadingBar(parent, x, y, w, h, flags, min, max, initialPos, UseSubproc);
	parent->AddChild(this);
}

static bool bDidInitCommonCtrls = false;

bool LoadingBar::MakeLoadingBar(Element* parent, int x, int y, int w, int h, long flags, int min, int max, int initialPos, bool UseSubproc)
{
	if (!parent)
		return false;

	if (!bDidInitCommonCtrls)
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_PROGRESS_CLASS;
		InitCommonControlsEx(&icex);
		bDidInitCommonCtrls = true;
	}

	m_Hwnd = CreateWindow(
		PROGRESS_CLASS,
		nullptr,
		flags,
		x, y,
		w, h,
		parent->GetHandle(),
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);
	
	SendMessage(m_Hwnd, PBM_SETRANGE, 0, MAKELPARAM(min, max));
	SendMessage(m_Hwnd, PBM_SETPOS, initialPos, 0);

	SetVisible(true);
	SetEnabled(true);

	SET_ELEMENT_USERDATA(m_Hwnd, this);
	if (UseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}

	return true;
}

void LoadingBar::SetRange(int min, int max)
{
	SendMessage(m_Hwnd, PBM_SETRANGE, 0, MAKELPARAM(min, max));
}

void LoadingBar::SetPosition(int pos)
{
	SendMessage(m_Hwnd, PBM_SETPOS, pos, 0);
}

int LoadingBar::GetPosition()
{
	return (int)SendMessage(m_Hwnd, PBM_GETPOS, 0, 0);
}

void LoadingBar::StepIt(int step)
{
	SendMessage(m_Hwnd, PBM_DELTAPOS, step, 0);
}

void LoadingBar::OnDeconstructor()
{
	DeleteThis();
}
