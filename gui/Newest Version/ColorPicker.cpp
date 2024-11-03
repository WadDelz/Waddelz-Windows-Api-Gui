#include "ColorPicker.h"
#include <commdlg.h>

using namespace gui;

COLORREF ColorPicker::DefColorPreset[16] = {
    RGB(0, 0, 0),
    RGB(15, 15, 15),
    RGB(30, 30, 30),
    RGB(45, 45, 45),
    RGB(60, 60, 60),
    RGB(75, 75, 75),
    RGB(90, 90, 90),
    RGB(105, 105, 105),
    RGB(120, 120, 120),
    RGB(135, 135, 135),
    RGB(150, 150, 150),
    RGB(175, 175, 175),
    RGB(200, 200, 200),
    RGB(215, 215, 215),
    RGB(232, 232, 232),
    RGB(255, 255, 255),
};

ColorPicker::ColorPicker()
{
	m_Parent = nullptr;
	m_Color = 0;
}

ColorPicker::ColorPicker(Element* element)
{
	m_Parent = element;
	m_Color = 0;
}

bool ColorPicker::ShowDialog(const int& flags, COLORREF customcolors[16])
{
    CHOOSECOLOR cc = { sizeof(CHOOSECOLOR) };
    cc.hwndOwner = (m_Parent) ? m_Parent->GetHandle() : nullptr;
    cc.lpCustColors = (customcolors) ? customcolors : DefColorPreset;
    cc.rgbResult = m_Color;
    cc.Flags = flags;

    if (ChooseColor(&cc)) 
    {
        m_Color = cc.rgbResult;
        return true;
    }
    return false;
}

COLORREF ColorPicker::GetColor()
{
    return m_Color;
}

void ColorPicker::SetElement(Element* element)
{
    m_Parent = element;
}

Element* ColorPicker::GetElement()
{
	return m_Parent;
}
