#include "Slider.h"

using namespace gui;

START_ELEMENT_SUBPROC(Slider)
DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, NO_PROC, 0);
END_PROC(CALL_DEF_SUBPROC())

Slider::Slider() : BaseClass()
{
	m_iMinValue = 0;
	m_iMaxValue = 0;

	SetClassname("Slider");
}

Slider::Slider(Element* parent, const int& command) : BaseClass()
{
	m_iMinValue = 0;
	m_iMaxValue = 0;

	SetClassname("Slider");
	MakeSlider(parent, 0, 0, 0, 0, DEF_FLAGS_SLIDER, command, false, 0, 10, 0);
	parent->AddChild(this);
}

Slider::Slider(Element* parent, const int& x, const int& y, const int& w, const int& h, const int& flags, const int& command, bool bUseSubproc, const int& minval, const int& maxval, const int& val, const char* classname) : BaseClass()
{
	m_iMinValue = 0;
	m_iMaxValue = 0;

	SetClassname(classname);
	MakeSlider(parent, x, y, w, h, flags, command, bUseSubproc, minval, maxval, val);
	parent->AddChild(this);
}

void Slider::OnDeconstructor()
{
	DeleteThis();
}

int Slider::GetValue()
{
	int value = SendMessage(m_Hwnd, TBM_GETPOS, 0, 0);
	return value;
}

void Slider::SetValue(int value)
{
	SendMessage(m_Hwnd, TBM_SETPOS, TRUE, value);
}

void Slider::GetRange(int& minval, int& maxval)
{
	minval = m_iMinValue;
	maxval = m_iMaxValue;
}

void Slider::SetRange(const int& minval, const int& maxval)
{
	m_iMinValue = minval;
	m_iMaxValue = maxval;
	SendMessage(m_Hwnd, TBM_SETRANGE, TRUE, MAKELONG(minval, maxval));
}

bool Slider::MakeSlider(Element* parent, int x, int y, int w, int h, long flags, int command, bool UseSubproc, const int& minval, const int& maxval, const int& val)
{
	m_iCommandId = command;

	if (!parent)
		return false;

	m_Hwnd = CreateWindow(
		TRACKBAR_CLASS,
		"",
		flags,
		x, y,
		w, h,
		parent->GetHandle(),
		(HMENU)command,
		GetModuleHandle(nullptr),
		nullptr
	);

	SetVisible(true);
	SetEnabled(true);
	SetRange(minval, maxval);
	SetValue(val);

	SET_ELEMENT_USERDATA(m_Hwnd, this);
	if (UseSubproc)
	{
		SetSubproc(ElementSubprocBase);
		ElementSubproc(m_Hwnd, WM_CREATE, 0, 0);
	}

	return true;
}