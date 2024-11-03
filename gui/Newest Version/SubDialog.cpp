#include "SubDialog.h"

using namespace gui;

START_ELEMENT_DLGPROC(SubDialog)
DEFINE_ELEMENT_PROC_RETURN(WM_CLOSE, OnClose, TRUE);
END_ELEMENT_PROC(FALSE)

START_ELEMENT_DLGPROC_DIFFERENT(SubDialog)
DEFINE_ELEMENT_PROC_RETURN(WM_CLOSE, OnCloseDifferent, TRUE);
END_ELEMENT_PROC(FALSE)

SubDialog::SubDialog()
{
	m_bDeleteOnClose = false;
}

void SubDialog::MakeDialog(Element* parent, int nResourceFile)
{
	m_Hwnd = CreateDialog(GetModuleHandle(nullptr), MAKEINTRESOURCE(nResourceFile), parent->GetHandle(), ElementDialogBase);
	ShowWindow(m_Hwnd, SW_SHOW);

	SET_ELEMENT_USERDATE(m_Hwnd, this);
	ElementDialogProc(m_Hwnd, WM_INITDIALOG, 0, 0);

	parent->AddChild(this);
}

void SubDialog::MakeDialogBox(Element* parent, int nResourceFile)
{
	parent->AddChild(this);
	DialogBoxParam(GetModuleHandle(nullptr), MAKEINTRESOURCE(nResourceFile), parent->GetHandle(), ElementDialogDiffBase, (LPARAM)this);
}

void SubDialog::SetDeleteOnClose(bool bDelete)
{
	m_bDeleteOnClose = bDelete;
}

void SubDialog::OnClose(ELEMENT_PROC_ITEMS)
{
	EndDialog(hwnd, IDCANCEL);
	
	if (m_bDeleteOnClose)
	{
		delete this;
	}
	else
	{
		DestroyWindow(m_Hwnd);

		if (m_Parent)
			m_Parent->RemoveChild(this);

		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			Element* curr = m_Children[i];
			if (!curr)
				continue;

			delete  curr;
		}

		if (m_szName)
			free(m_szName);

		if (m_szClassName)
			free(m_szClassName);
	}
}

void SubDialog::OnCloseDifferent(ELEMENT_PROC_ITEMS)
{
	if (m_Parent)
		m_Parent->SetFocusToThis();

	EndDialog(hwnd, IDCANCEL);

	if (m_bDeleteOnClose)
	{
		delete this;
	}
	else
	{
		DestroyWindow(m_Hwnd);

		if (m_Parent)
			m_Parent->RemoveChild(this);

		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			Element* curr = m_Children[i];
			if (!curr)
				continue;

			delete  curr;
		}

		if (m_szName)
			free(m_szName);

		if (m_szClassName)
			free(m_szClassName);
	}
}