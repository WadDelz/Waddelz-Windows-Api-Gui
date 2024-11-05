#include "SubDialog.h"
#include "PropertyPage.h"

using namespace gui;

START_ELEMENT_DLGPROC(SubDialog)
DEFINE_ELEMENT_PROC_RETURN(WM_CLOSE, OnClose, TRUE);
END_ELEMENT_PROC(FALSE)

START_ELEMENT_DLGPROC_DIFFERENT(SubDialog)
DEFINE_ELEMENT_PROC_RETURN(WM_CLOSE, OnCloseDifferent, TRUE);
END_ELEMENT_PROC(FALSE)

SubDialog::SubDialog() : BaseClass()
{
	m_bIsSubDialog = true;
	SetClassname("SubDialog");
}

void SubDialog::MakeDialog(Element* parent, int nResourceFile)
{
	m_Hwnd = CreateDialog(GetModuleHandle(nullptr), MAKEINTRESOURCE(nResourceFile), parent->GetHandle(), ElementDialogBase);
	ShowWindow(m_Hwnd, SW_SHOW);

	parent->AddChild(this);

	SET_ELEMENT_USERDATA(m_Hwnd, this);
	ElementDialogProc(m_Hwnd, WM_INITDIALOG, 0, 0);
}

void SubDialog::MakeDialogBox(Element* parent, int nResourceFile)
{
	parent->AddChild(this);
	DialogBoxParam(GetModuleHandle(nullptr), MAKEINTRESOURCE(nResourceFile), parent->GetHandle(), ElementDialogDiffBase, (LPARAM)this);
}

void SubDialog::OnClose(ELEMENT_PROC_ITEMS)
{
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG)ElementDialogEmpty);
	EndDialog(hwnd, IDCANCEL);
	
	m_Hwnd = nullptr;
	bDeleteThisHack = true;
	delete this;
}

void SubDialog::OnCloseDifferent(ELEMENT_PROC_ITEMS)
{
	if (m_Parent)
		m_Parent->SetFocusToThis();

	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG)ElementDialogEmpty);
	EndDialog(hwnd, IDCANCEL);

	m_Hwnd = nullptr;
	bDeleteThisHack = true;
	delete this;
}

void SubDialog::DeleteThis()
{
	if (m_Hwnd)
		DestroyWindow(m_Hwnd);

	if (m_Parent)
		m_Parent->RemoveChild(this);

	if (m_PropertyPage)
		m_PropertyPage->RemoveElement(this, false);

	for (unsigned int i = 0; i < m_Children.size(); i++)
	{
		Element* curr = m_Children[i];
		if (!curr)
			continue;

		curr->m_Hwnd = nullptr;
		curr->SetParent(nullptr);
		delete  curr;
	}
	
	if (m_szName)
		free(m_szName);

	if (m_szClassName)
		free(m_szClassName);
}

SubDialog::~SubDialog()
{
	DeleteThis();
}
